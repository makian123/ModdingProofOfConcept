#pragma once

#include <functional>
#include <string_view>

namespace ModFramework {
	void LoadMod(std::string_view modPath);
	void UnloadMod(std::string_view modPath);

	void RegisterCallback(std::function<void(int)> func, void *modAddr);

	void TriggerCallbacks();
}