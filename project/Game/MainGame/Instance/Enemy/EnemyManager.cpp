#include "EnemyManager.h"

#include "Enemy.h"

#include "Game/MainGame/Misc/GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Module/World/Collision/CollisionManager.h>
#include <Engine/Module/World/WorldManager.h>

EnemyManager::EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_, Reference<WorldManager> worldManager_) :
	collisionManager(collisionManager_),
	callback(callback_),
	worldManager(worldManager_) {
	add_enemy(Vector3{ 0,0,0 });
	add_enemy(Vector3{ 2,0,0 });
}

void EnemyManager::begin() {
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->begin();
	}
}

void EnemyManager::update() {
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->update();
	}
}

void EnemyManager::transfer() {
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->transfer();
	}
}

void EnemyManager::late_update() {
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->late_update();
	}
}

void EnemyManager::draw() const {
	for (const std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->draw();
	}
}

void EnemyManager::add_enemy(Vector3 position) {
	std::unique_ptr<Enemy>& enemy = enemies.emplace_back(worldManager->create<Enemy>(nullptr, false, position));
	enemy->initialize();
	callback->register_enemy(enemy);
	collisionManager->register_collider("Enemy", enemy->get_collider());
}

std::list<std::unique_ptr<Enemy>>::iterator EnemyManager::erase_enemy(const std::list<std::unique_ptr<Enemy>>::iterator& itr) {
	callback->unregister_enemy((*itr).get());
	return enemies.erase(itr);
}
