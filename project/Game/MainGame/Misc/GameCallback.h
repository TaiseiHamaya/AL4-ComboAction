#pragma once

#include "Engine/Module/World/Collision/CollisionCallbackManager.h"

#include "../Instance/Enemy/Enemy.h"

#include <Engine/Utility/Template/Reference.h>

class GameCallback final : public CollisionCallbackManager {
public:
	GameCallback();
	~GameCallback() = default;

	__NON_COPYABLE_CLASS(GameCallback)

public:
	void register_enemy(Reference<Enemy> enemy);

private:
	void Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs));

private:
	std::unordered_map<BaseCollider*, Reference<Enemy>> getEnemyByCollider;
};

