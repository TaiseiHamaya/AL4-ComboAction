#pragma once

#include <list>

#include <Library/Utility/Template/Reference.h>
#include <Library/Math/Vector3.h>

class Enemy;
class CollisionManager;
class GameCallback;
class WorldManager;
class DeadEnemy;

class EnemyManager {
public:
	EnemyManager(Reference<CollisionManager> collisionManager_, Reference<GameCallback> callback_, Reference<WorldManager> worldManager_);
	~EnemyManager();

public:
	void begin();

	void update();
	void transfer();
	void late_update();
	void draw() const;

public:
	bool is_hitstop() const { return isHitStop; }
	bool is_clear() const;
	void add_enemy(Vector3 position);
	std::list<std::unique_ptr<Enemy>>::iterator erase_enemy(const std::list<std::unique_ptr<Enemy>>::iterator& itr);

private:
	std::list<std::unique_ptr<Enemy>> enemies;
	std::list<std::unique_ptr<DeadEnemy>> removedEnemies;

	Reference<GameCallback> callback;
	Reference<CollisionManager> collisionManager;
	Reference<WorldManager> worldManager;
	float hitStopTimer{ 0 };
	bool isHitStop{ false };

};
