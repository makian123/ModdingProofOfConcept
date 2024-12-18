#include "../include/framework.h"
#include <unordered_map>
#include <string>

//#if defined(WIN32)
#include <Windows.h>
//#endif

struct Mod {
	void (*initFunc)(void*) = nullptr;
	void (*stopFunc)() = nullptr;
	std::vector<std::function<void(int)>> callbacks;
};

namespace ModFramework {

	std::unordered_map<std::string, Mod> mods;
	void LoadMod(std::string_view modPath) {
		const std::string path = std::string(modPath);
		Mod& mod = mods[path];
//#if defined(WIN32)
		HINSTANCE procDLL = LoadLibraryA(path.c_str());
		if (!procDLL) {
			// Error loading dll
			return;
		}

		mod.initFunc = reinterpret_cast<decltype(mod.initFunc)>(GetProcAddress(procDLL, "start"));
		if (!mod.initFunc) {
			return;
		}

		mod.stopFunc = reinterpret_cast<decltype(mod.stopFunc)>(GetProcAddress(procDLL, "end"));
		if (!mod.stopFunc) {
			return;
		}
//#endif

		mod.initFunc(&mod);
	}
	void UnloadMod(std::string_view modPath) {
		const std::string path = std::string(modPath);
		if(!mods.contains(std::string(path))) return;
		mods[path].stopFunc();

		mods.erase(path);
	}

	void RegisterCallback(std::function<void(int)> func, void *modAddr) {
		auto& mod = *reinterpret_cast<Mod*>(modAddr);
		mod.callbacks.push_back(func);
	}
	void TriggerCallbacks() {
		for (auto& [name, mod] : mods) {
			for (auto& callback : mod.callbacks) {
				callback(51);
			}
		}
	}
}