#include "GameFramework.h"

#include "Engine/Runtime/Scene/SceneManager.h"
#include "Engine/Runtime/WorldClock/WorldClock.h"

#include "SceneFactoryGame.h"

void GameFramework::initialize() {
	SceneManager::SetFactory<SceneFactoryGame>();

#ifdef _DEBUG
	WorldClock::IsFixDeltaTime(true);
#endif // _DEBUG

	Framework::initialize();
}
