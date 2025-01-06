#pragma once

#include "Engine/Module/World/Collision/CollisionCallbackManager.h"

#include "../Instance/Enemy/Enemy.h"

class GameCallback final : public CollisionCallbackManager {
public:
	GameCallback();
	~GameCallback() = default;

	__NON_COPYABLE_CLASS(GameCallback)

public:
	void register_enemy(Enemy* enemy);

private:
	void Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs));

private:
	std::unordered_map<BaseCollider*, Enemy*> getEnemyByCollider;
};

