#include "GameFramework.h"

#include "Engine/Runtime/Scene/SceneManager.h"

#include "SceneFactoryGame.h"

void GameFramework::initialize() {
	SceneManager::SetFactory<SceneFactoryGame>();
	WorldClock::IsFixDeltaTime(true);

	Framework::initialize();
}
