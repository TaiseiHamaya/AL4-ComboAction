#pragma once

#include <Engine/Module/World/Mesh/StaticMeshInstance.h>

#include <memory>

class SphereCollider;

class Enemy : public StaticMeshInstance {
public:
	Enemy(Vector3 translate);
	~Enemy() = default;

public:
	void initialize();
	void begin() override;
	void update() override;
	void transfer() noexcept override;
	void draw() const override;

public:
	void take_damage(float Time);
	const std::shared_ptr<SphereCollider>& get_collider() const { return collider; };

	bool is_destroy() const { return isDead; }

	const Vector3& knockback_vector() const { return knockback; }
	const Vector3& get_velocity() const { return velocity; }
	void translate_force(const Vector3& translate_) { translate = translate_; };

private:
	Vector3 translate;
	Vector3 direction;
	Vector3 velocity;

	std::unique_ptr<StaticMeshInstance> shadow;

	float invincibleTimer{ 0 };

	Vector3 knockback;
	std::shared_ptr<SphereCollider> collider;

	float hitPoint{ 15 };
	bool isDead{ false };

public:
	inline static Reference<WorldInstance> player{};
};
