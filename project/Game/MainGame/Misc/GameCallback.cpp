#include "GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>

GameCallback::GameCallback(
	Reference<const WorldInstance> player_
) :
	player(player_) {
	callbackFunctions.emplace(
		CallbackMapKey("AttackCollider", "Enemy"),
		CallbackFunctions{
			nullptr,
			std::bind(&GameCallback::Callback, this, __CALLBACK_PLACEHOLDERS_12),
			nullptr
		}
	);
}

void GameCallback::begin() {
	for (auto& animation : hitAnimations) {
		animation.begin();
	}
}

void GameCallback::update() {
	for (auto& animation : hitAnimations) {
		animation.update();
	}

	hitAnimations.remove_if([](auto& elem) {return elem.is_end(); });
}

void GameCallback::transfer() {
	for (auto& animation : hitAnimations) {
		animation.transfer();
	}
}

void GameCallback::draw_billboard() const {
	for (auto& animation : hitAnimations) {
		animation.draw_billboard();
	}
}

void GameCallback::draw_particle() const {
	for (auto& animation : hitAnimations) {
		animation.draw_particle();
	}
}

void GameCallback::register_enemy(Reference<Enemy> enemy) {
	getEnemyByCollider.emplace(
		enemy->get_collider().get(), enemy
	);
}

void GameCallback::unregister_enemy(Reference<const Enemy> enemy) {
	getEnemyByCollider.erase(enemy->get_collider().get());
}

void GameCallback::Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs)) {
	Reference<Enemy> enemy;
	Vector3 enemyCollisionPosition;
	if (getEnemyByCollider.contains(lhs)) {
		enemy = getEnemyByCollider.at(lhs);
		enemyCollisionPosition = lhs->world_position();
	}
	if (getEnemyByCollider.contains(rhs)) {
		enemy = getEnemyByCollider.at(rhs);
		enemyCollisionPosition = rhs->world_position();
	}
	if (enemy) {
		enemy->take_damage(0.3f);
	}

	Vector3 direction = (player->world_position() - enemyCollisionPosition).normalize_safe(1e-6f, CVector3::ZERO);
	Vector3 position = enemyCollisionPosition + direction * 0.5f;

	hitAnimations.emplace_back(std::move(position));
}
