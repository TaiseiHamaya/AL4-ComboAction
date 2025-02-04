#pragma once

#include <list>

#include "../Instance/Enemy/Enemy.h"

#include <Engine/Module/World/Collision/CollisionCallbackManager.h>
#include <Engine/Module/World/Particle/ParticleEmitterInstance.h>
#include <Engine/Module/World/Mesh/StaticMeshInstance.h>
#include <Library/Utility/Template/Reference.h>

#include "Game/MainGame/Instance/Effects/HitAnimation.h"

class GameCallback final : public CollisionCallbackManager {
public:
	GameCallback(
		Reference<const WorldInstance> player
	);
	~GameCallback() = default;

	__NON_COPYABLE_CLASS(GameCallback)

public:
	void begin();
	void update();
	void transfer();
	void draw_billboard() const;
	void draw_particle() const;

public:
	void register_enemy(Reference<Enemy> enemy);
	void unregister_enemy(Reference<const Enemy> enemy);

private:
	void callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs));

private:
	std::list<HitAnimation> hitAnimations;
	Reference<const WorldInstance> player;
	std::unordered_map<BaseCollider*, Reference<Enemy>> getEnemyByCollider;
};

