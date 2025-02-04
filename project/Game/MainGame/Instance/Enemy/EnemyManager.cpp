#include "EnemyManager.h"

#include "Enemy.h"
#include "DeadEnemy.h"

#include "Game/MainGame/Misc/GameCallback.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Module/World/Collision/CollisionManager.h>
#include <Engine/Module/World/WorldManager.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>

EnemyManager::EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_, Reference<WorldManager> worldManager_) :
	collisionManager(collisionManager_),
	callback(callback_),
	worldManager(worldManager_) {
	add_enemy(Vector3{ 0,0,3 });
	add_enemy(Vector3{ 4,0,3 });
	add_enemy(Vector3{ -4,0,3 });
}

EnemyManager::~EnemyManager() = default;

void EnemyManager::begin() {
	hitStopTimer -= WorldClock::DeltaSeconds();
	if (hitStopTimer <= 0) {
		isHitStop = false;
	}
	else {
		for (std::unique_ptr<DeadEnemy>& enemy : removedEnemies) {
			enemy->update();
		}
		return;
	}
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->begin();
	}
}

void EnemyManager::update() {
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->update();
	}
	for (std::unique_ptr<DeadEnemy>& enemy : removedEnemies) {
		enemy->update();
	}

	auto removed = enemies.remove_if([&](const std::unique_ptr<Enemy>& elem) {
		if (elem->is_destroy()) {
			removedEnemies.emplace_back(
				worldManager->create<DeadEnemy>(
					nullptr, false,
					elem->world_position(),
					elem->get_transform().get_quaternion(),
					elem->knockback_vector()
				));
			isHitStop = true;
			hitStopTimer = 0.5f;
			return true;
		}
		return false;
	});

	removedEnemies.remove_if(
		[](std::unique_ptr<DeadEnemy>& elem) { return elem->is_destroy(); }
	);
}

void EnemyManager::transfer() {
	for (const std::unique_ptr<DeadEnemy>& enemy : removedEnemies) {
		enemy->transfer();
	}
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
	for (const std::unique_ptr<DeadEnemy>& enemy : removedEnemies) {
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
