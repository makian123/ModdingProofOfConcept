#include "../TestProgram/include/framework.h"

int main() {
	ModFramework::LoadMod("mods/TestMod.dll");

	ModFramework::TriggerCallbacks();

	ModFramework::UnloadMod("mods/TestMod.dll");
}