#include "EnemyManager.h"

#include "Enemy.h"

#include "Game/MainGame/Misc/GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Module/World/Collision/CollisionManager.h>

EnemyManager::EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_) :
	collisionManager(collisionManager_),
	callback(callback_) {
	add_enemy(Vector3{ 0,0,0 });
	add_enemy(Vector3{ 2,0,0 });
}

void EnemyManager::begin() {
	for (Enemy& enemy : enemies) {
		enemy.begin();
	}
}

void EnemyManager::update() {
	for (Enemy& enemy : enemies) {
		enemy.update();
	}
}

void EnemyManager::begin_rendering() {
	for (Enemy& enemy : enemies) {
		enemy.begin_rendering();
	}
}

void EnemyManager::late_update() {
	for (Enemy& enemy : enemies) {
		enemy.late_update();
	}
}

void EnemyManager::draw() const {
	for (const Enemy& enemy : enemies) {
		enemy.draw();
	}
}

void EnemyManager::add_enemy(Vector3 position) {
	Enemy& enemy = enemies.emplace_back(position);
	callback->register_enemy(enemy);
	collisionManager->register_collider("Enemy", enemy.get_collider());
}

std::list<Enemy>::iterator EnemyManager::erase_enemy(const std::list<Enemy>::iterator& itr) {
	callback->unregister_enemy(std::to_address(itr));
	return enemies.erase(itr);
}
