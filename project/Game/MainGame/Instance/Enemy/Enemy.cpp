#include "Enemy.h"

#include <Engine/Utility/Tools/SmartPointer.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Utility/Tools/RandomEngine.h>

Enemy::Enemy() :
	MeshInstance("Enemy.gltf") {
	collider = eps::CreateUnique<SphereCollider>();
	collider->set_parent(*this);
}

void Enemy::update() {
	invincibleTimer -= WorldClock::DeltaSeconds();
	if (invincibleTimer <= 0) {
		collider->set_active(true);
	}

	if (invincibleTimer >= 0) {
		bool singbit = std::signbit(std::sin(invincibleTimer * PI * 60));
		if (singbit) {
			transform.set_translate(translate + direction * invincibleTimer * 10);
		}
		else {
			transform.set_translate(translate);
		}
	}
	else {
		transform.set_translate(translate);
	}
}

Vector3 RandomOnSphere() {
	float cosTheta = -2.0f * RandomEngine::Random01Closed() + 1.0f;
	float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
	float phi = PI2 * RandomEngine::Random01Closed();
	return { sinTheta * std::cos(phi), sinTheta * std::sin(phi), cosTheta };
}

void Enemy::take_damage(float InvincibleTime) {
	invincibleTimer = InvincibleTime;
	collider->set_active(false);
	direction = RandomOnSphere();
}
