#include "GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>

GameCallback::GameCallback() {
	callbackFunctions.emplace(
		CallbackMapKey("AttackCollider", "Enemy"),
		CallbackFunctions{
			nullptr,
			std::bind(&GameCallback::Callback, this, __CALLBACK_PLACEHOLDERS_12),
			nullptr
		}
	);
}

void GameCallback::register_enemy(Reference<Enemy> enemy) {
	getEnemyByCollider.emplace(
		enemy->get_collider().get(), enemy
	);
}

void GameCallback::Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs)) {
	Reference<Enemy> enemy;
	if (getEnemyByCollider.contains(lhs)) {
		enemy = getEnemyByCollider.at(lhs);
	}
	if (getEnemyByCollider.contains(rhs)) {
		enemy = getEnemyByCollider.at(rhs);
	}
	if (enemy) {
		enemy->take_damage(0.3f);
	}
}
