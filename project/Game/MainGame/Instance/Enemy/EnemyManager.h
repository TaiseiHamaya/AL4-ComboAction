#pragma once

#include <list>

#include <Library/Utility/Template/Reference.h>
#include <Library/Math/Vector3.h>

class Enemy;
class CollisionManager;
class GameCallback;
class WorldManager;

class EnemyManager {
public:
	EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_, Reference<WorldManager> worldManager_);
	~EnemyManager() = default;

public:
	void begin();
	void update();
	void transfer();
	void late_update();
	void draw() const;

public:
	void add_enemy(Vector3 position);
	std::list<std::unique_ptr<Enemy>>::iterator erase_enemy(const std::list<std::unique_ptr<Enemy>>::iterator& itr);

private:
	std::list<std::unique_ptr<Enemy>> enemies;

	Reference<GameCallback> callback;
	Reference<CollisionManager> collisionManager;
	Reference<WorldManager> worldManager;
};
