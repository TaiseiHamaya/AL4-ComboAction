#pragma once

#include <Engine/Runtime/Scene/BaseScene.h>

#include <Engine/Module/Render/RenderPath/RenderPath.h>
#include <Engine/Module/World/Light/DirectionalLight/DirectionalLightInstance.h>
#include <Engine/Module/World/Camera/Camera3D.h>
#include <Engine/Module/World/Collision/CollisionManager.h>

#include "Game/MainGame/Instance/Player/Player.h"
#include "Game/MainGame/Instance/Enemy/Enemy.h"
#include "Game/MainGame/Instance/Camera/FollowCamera.h"

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
	std::unique_ptr<DirectionalLightInstance> directionalLight;
	std::unique_ptr<CollisionManager> collisionManager;
	std::unique_ptr<FollowCamera> camera3D;

	std::unique_ptr<Player> player;
	std::unique_ptr<Enemy> enemy;
};
