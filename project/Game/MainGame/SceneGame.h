#pragma once

#include <Engine/Runtime/Scene/BaseScene.h>

#include <Engine/Module/DrawExecutor/LightingExecutor/DirectionalLightingExecutor.h>
#include <Engine/Module/Render/RenderPath/RenderPath.h>
#include <Engine/Module/World/Camera/Camera3D.h>
#include <Engine/Module/World/Collision/CollisionManager.h>
#include <Engine/Module/World/Light/DirectionalLight/DirectionalLightInstance.h>
#include <Engine/Module/World/Sprite/SpriteInstance.h>
#include <Engine/Module/World/WorldManager.h>

#include "Game/MainGame/Instance/Camera/FollowCamera.h"
#include "Game/MainGame/Instance/Enemy/EnemyManager.h"
#include "Game/MainGame/Instance/Player/Player.h"
#include "Game/MainGame/Misc/GameCallback.h"

class SceneGame final : public BaseScene {
public:
	void load() override;
	void initialize() override;
	void update() override;
	void begin_rendering() override;
	void late_update() override;
	void draw() const override;

#ifdef _DEBUG
public:
	void debug_update() override;
#endif // _DEBUG

private:
	std::unique_ptr<RenderPath> renderPath;
	std::unique_ptr<WorldManager> worldManager;

	std::unique_ptr<DirectionalLightingExecutor> directionalLightingExecutor;

	std::unique_ptr<DirectionalLightInstance> directionalLight;
	std::unique_ptr<CollisionManager> collisionManager;

	std::unique_ptr<FollowCamera> camera3D;

	std::unique_ptr<Player> player;
	std::unique_ptr<StaticMeshInstance> playerShadow;
	std::unique_ptr<EnemyManager> enemyManager;
	std::unique_ptr<StaticMeshInstance> skydome;

	std::unique_ptr<SpriteInstance> keySprite;

	Reference<GameCallback> callback;
};
