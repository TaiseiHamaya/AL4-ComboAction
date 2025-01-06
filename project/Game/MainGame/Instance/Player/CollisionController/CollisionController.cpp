#include "CollisionController.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Module/World/Collision/CollisionManager.h>
#include <Engine/Module/World/WorldInstance/WorldInstance.h>

CollisionController::CollisionController() {
	collider = std::make_shared<SphereCollider>();
	collider->initialize();
	collisionManager->register_collider("AttackCollider", collider);
	if (parent) {
		collider->set_parent(*parent);
	}
	reset();
}

void CollisionController::reset() {
	timer = 0;
	next = curve.begin();
}

void CollisionController::update() {
	timer += WorldClock::DeltaSeconds();

	if (timer <= BeginTime) {
		collider->set_active(false);
	}
	else if (timer <= EndTime) {
		collider->set_active(true);

		Vector3 nowTranslate;
		if (timer >= next->first) {
			++next;
		}
		const float& NextCurveTime = next->first;
		const Vector3& NextTranslate = next->second;
		if (next == curve.end()) {
			nowTranslate = CVector3::ZERO;
		}
		else if (next == curve.begin()) {
			nowTranslate = NextTranslate;
		}
		else {
			AnimationCurve::const_iterator prev = std::prev(next);
			const float& PrevCurveTime = prev->first;
			const Vector3& PrevTranslate = prev->second;

			float parametric = (timer - PrevCurveTime) / (NextCurveTime - PrevCurveTime);
			nowTranslate = Vector3::Lerp(PrevTranslate, NextTranslate, parametric);
		}
		collider->get_transform().set_translate(nowTranslate);
	}
	else {
		collider->set_active(false);
	}
}
