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

private:
	Vector3 translate;
	Vector3 direction;

	std::unique_ptr<StaticMeshInstance> shadow;

	float invincibleTimer{ 0 };
	std::shared_ptr<SphereCollider> collider;

	Vector3 knockback;

public:
	inline static Reference<WorldInstance> player{};
};
