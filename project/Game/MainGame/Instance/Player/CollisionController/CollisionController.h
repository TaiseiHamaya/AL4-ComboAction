#pragma once

#include <memory>
#include <map>

class BaseCollider;
class CollisionManager;

#include <Library/Math/Vector3.h>

class CollisionController {
private:
	using AnimationCurve = std::map<float, Vector3>;

public:
	CollisionController();
	~CollisionController() = default;

public:
	void reset();
	void update();

private:
	float timer;
	float BeginTime;
	float EndTime;
	std::shared_ptr<BaseCollider> collider;

	AnimationCurve::const_iterator next;
	AnimationCurve curve;

public:
	inline static CollisionManager* collisionManager{ nullptr };
};
