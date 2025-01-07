#pragma once

#include <list>

#include "../Instance/Enemy/Enemy.h"

#include <Engine/Module/World/Collision/CollisionCallbackManager.h>
#include <Engine/Module/World/Particle/ParticleEmitterInstance.h>
#include <Engine/Module/World/Mesh/MeshInstance.h>
#include <Engine/Utility/Template/Reference.h>

class GameCallback final : public CollisionCallbackManager {
public:
	GameCallback(
		Reference<ParticleEmitterInstance> emitter_,
		Reference<MeshInstance> mesh,
		Reference<const WorldInstance> player
	);
	~GameCallback() = default;

	__NON_COPYABLE_CLASS(GameCallback)

public:
	void update();
	void register_enemy(Reference<Enemy> enemy);

public:
	bool is_reset() const { return onCollision; };

private:
	void Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs));

private:
	bool onCollision{ false };

	Reference<ParticleEmitterInstance> emitter;
	Reference<MeshInstance> mesh;
	Reference<const WorldInstance> player;
	std::unordered_map<BaseCollider*, Reference<Enemy>> getEnemyByCollider;
};

