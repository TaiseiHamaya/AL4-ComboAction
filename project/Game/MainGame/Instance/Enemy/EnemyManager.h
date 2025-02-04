#pragma once

#include <list>

#include <Engine/Utility/Template/Reference.h>

#include <Library/Math/Vector3.h>

class Enemy;
class CollisionManager;
class GameCallback;

class EnemyManager {
public:
	EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_);
	~EnemyManager() = default;

public:
	void begin();
	void update();
	void begin_rendering();
	void late_update();
	void draw() const;

public:
	void add_enemy(Vector3 position);
	std::list<Enemy>::iterator erase_enemy(const std::list<Enemy>::iterator& itr);

private:
	std::list<Enemy> enemies;

	Reference<GameCallback> callback;
	Reference<CollisionManager> collisionManager;
};
