#pragma once

#include <Engine/Module/World/Mesh/MeshInstance.h>

#include <memory>

class SphereCollider;

class Enemy : public MeshInstance {
public:
	Enemy();
	~Enemy() = default;

public:
	void update() override;

public:
	void take_damage(float Time);
	const std::shared_ptr<SphereCollider>& get_collider() const { return collider; };

private:
	Vector3 translate;
	Vector3 direction;

	float invincibleTimer{ 0 };
	std::shared_ptr<SphereCollider> collider;
};
