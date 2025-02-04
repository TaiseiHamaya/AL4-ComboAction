#include <windows.h>

#include <memory>

#include "Game/GameFramework.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<Framework> framework =
		std::make_unique<GameFramework>();

	framework->run();

	framework.reset();

	return 0;
}
