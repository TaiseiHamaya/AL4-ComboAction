#include "SceneFactoryGame.h"

#include "./Debug/DebugScene.h"
#include "./Title/SceneTitle.h"
#include "./MainGame/SceneGame.h"
#include "./Clear/SceneClear.h"

std::unique_ptr<BaseScene> SceneFactoryGame::initialize_scene() {
#ifdef _DEBUG
	return std::make_unique<DebugScene>();
#else
	return std::make_unique<SceneTitle>();
#endif // _DEBUG
}

std::unique_ptr<BaseScene> SceneFactoryGame::create_scene(int32_t next) {
	switch (next) {
	case SceneList::Title:
		return std::make_unique<SceneTitle>();
		break;
	case SceneList::Game:
		return std::make_unique<SceneGame>();
		break;
	case SceneList::Claer:
		return std::make_unique<SceneClear>();
		break;
	}
	return nullptr;
}
