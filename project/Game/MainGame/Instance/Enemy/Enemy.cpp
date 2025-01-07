#include "Enemy.h"

#include <Engine/Utility/Tools/SmartPointer.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Utility/Tools/RandomEngine.h>

#include "Game/Util/RandomUtil.h"

Enemy::Enemy() :
	MeshInstance("Enemy.gltf") {
	collider = eps::CreateUnique<SphereCollider>();
	collider->initialize();
	collider->set_parent(*this);
	collider->set_radius(0.5f);
	collider->get_transform().set_translate_y(0.5f);
}

void Enemy::update() {
	invincibleTimer -= WorldClock::DeltaSeconds();
	if (invincibleTimer <= 0) {
		collider->set_active(true);
	}

	if (invincibleTimer >= 0) {
		bool singbit = std::signbit(std::sin(invincibleTimer * PI * 20));
		if (singbit) {
			transform.set_translate(translate + direction * invincibleTimer * 1);
		}
		else {
			transform.set_translate(translate);
		}
	}
	else {
		transform.set_translate(translate);
	}
}

void Enemy::take_damage(float InvincibleTime, const Vector3& colliderTranslate) {
	invincibleTimer = InvincibleTime;
	collider->set_active(false);
	direction = RandomOnSphere();
}
