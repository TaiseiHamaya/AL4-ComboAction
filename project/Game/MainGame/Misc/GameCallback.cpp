#include "GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>

GameCallback::GameCallback(
	Reference<ParticleEmitterInstance> emitter_,
	Reference<MeshInstance> mesh_,
	Reference<const WorldInstance> player_
) :
	emitter(emitter_),
	mesh(mesh_),
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

void GameCallback::update() {
	onCollision = false;
}

void GameCallback::register_enemy(Reference<Enemy> enemy) {
	getEnemyByCollider.emplace(
		enemy->get_collider().get(), enemy
	);
}

void GameCallback::Callback(__CALLBACK_ARGUMENT_DEFAULT(lhs, rhs)) {
	Reference<Enemy> enemy;
	Vector3 enemyCollisionPosition;
	if (getEnemyByCollider.contains(lhs)) {
		enemy = getEnemyByCollider.at(lhs);
		enemyCollisionPosition= lhs->world_position();
	}
	if (getEnemyByCollider.contains(rhs)) {
		enemy = getEnemyByCollider.at(rhs);
		enemyCollisionPosition= rhs->world_position();
	}
	if (enemy) {
		enemy->take_damage(0.3f);
	}

	Vector3 direction = (player->world_position() - enemyCollisionPosition).normalize_safe(1e-6f, CVector3::ZERO);
	Vector3 position = enemyCollisionPosition + direction * 0.5f;
	emitter->get_transform().set_translate(position);
	emitter->emit();

	const Quaternion& rotation = mesh->get_transform().get_quaternion();
	mesh->get_transform().set_translate(position + CVector3::BASIS_Z * rotation);
	onCollision = true;
}
