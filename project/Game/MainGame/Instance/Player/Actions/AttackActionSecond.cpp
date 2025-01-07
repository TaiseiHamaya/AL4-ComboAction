#include "AttackActionSecond.h"

AttackActionSecond::AttackActionSecond() {
	useAnimationName = "AttackSecond";
	bufferingableParametric = 0.5f;
	transitionableParametric= 0.9f;

	collisionController.initialize(JsonResource{ CollisionController::ActionJsonDir / "second.json" });
	guiTag = "AttackActionSecond";
}

void AttackActionSecond::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionSecond::update() {
	BaseAttackAction::update();
}
