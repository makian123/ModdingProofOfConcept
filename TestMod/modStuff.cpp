#include <iostream>
#include "../TestProgram/include/framework.h"

extern "C" {
	void hook(int asd) {
		std::cout << "Callback: " << asd << '\n';
	}

	void __declspec(dllexport) start(void * modAddr) {
		std::cout << "Starting the mod\n";
		ModFramework::RegisterCallback(hook, modAddr);
	}
	void __declspec(dllexport) end() {
		std::cout << "Ending the mod\n";
	}
}