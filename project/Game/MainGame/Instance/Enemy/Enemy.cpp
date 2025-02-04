#include "Enemy.h"

#include <Library/Utility/Tools/SmartPointer.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Library/Utility/Tools/RandomEngine.h>
#include <Engine/Module/World/WorldManager.h>

#include "Game/Util/RandomUtil.h"

Enemy::Enemy(Vector3 translate_) :
	StaticMeshInstance("Enemy.gltf") {

	translate = translate_;
}

void Enemy::initialize() {
	collider = world_manager()->create<SphereCollider>(this, false);
	collider->set_radius(0.5f);
	collider->get_transform().set_translate_y(0.5f);

	shadow = world_manager()->create<StaticMeshInstance>(nullptr, false, "shadow.gltf");
}

void Enemy::begin() {
	StaticMeshInstance::begin();
	shadow->begin();
}

void Enemy::update() {
	invincibleTimer -= WorldClock::DeltaSeconds();

	if (translate.y >= 0) {
		knockback.x *= 0.8f;
		knockback.z *= 0.8f;
		knockback.y += -9.8f * WorldClock::DeltaSeconds();
		translate += knockback * WorldClock::DeltaSeconds();
	}
	if (translate.y < 0) {
		translate.y = 0;
		knockback = CVector3::ZERO;
	}

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

	shadow->update();
	float scaleBase = 1 / (get_transform().get_translate().y + 2);
	shadow->get_transform().set_scale({ scaleBase, scaleBase, scaleBase });
	shadow->get_transform().set_translate(world_position());
	shadow->get_transform().set_translate_y(0.01f);
}

void Enemy::transfer() noexcept {
	StaticMeshInstance::transfer();
	shadow->transfer();
}

void Enemy::draw() const {
	StaticMeshInstance::draw();
	shadow->draw();
}

void Enemy::take_damage(float InvincibleTime) {
	invincibleTimer = InvincibleTime;
	collider->set_active(false);
	direction = RandomOnSphere();
	Vector3 xzknowkbackDirection = (world_position() - player->world_position());
	xzknowkbackDirection.y = 0;
	knockback = xzknowkbackDirection.normalize_safe(1e-4f, CVector3::ZERO) * 3.f + Vector3{ 0,2.0f, 0 };
}
