#pragma once

#include <memory>
#include <map>

class SphereCollider;
class CollisionManager;
class WorldInstance;
class WorldManager;

#include <Library/Math/Vector3.h>

#include <Library/Utility/Template/Reference.h>
#include <Engine/Assets/Json/JsonAsset.h>

class CollisionController {
private:
	using AnimationCurve = std::map<float, Vector3>;

public:
	CollisionController();
	~CollisionController() = default;

public:
	void initialize(JsonAsset json);
	void reset();
	void update();
	void disable_force();

#ifdef _DEBUG
public:
	void debug_gui();
#endif // _DEBUG

private:
	float timer;
	float BeginTime;
	float EndTime;
	std::shared_ptr<SphereCollider> collider;

	AnimationCurve::const_iterator next;
	AnimationCurve curve;

#ifdef _DEBUG
public:
	struct DebugValue {
		float colliderSize;
		float key;
		Vector3 value;
		char file[128] = { 0 };
	} debugValue;
#endif // _DEBUG

public:
	inline static const std::filesystem::path ActionJsonDir{ "./Resources/Game/Json" };

	inline static Reference<CollisionManager> collisionManager{ nullptr };
	inline static Reference<WorldInstance> parent{ nullptr };
	inline static Reference<WorldManager> worldManager{};
};
