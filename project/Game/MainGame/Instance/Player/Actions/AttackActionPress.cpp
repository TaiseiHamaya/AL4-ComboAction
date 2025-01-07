#include "AttackActionPress.h"

AttackActionPress::AttackActionPress() {
	useAnimationName = "AttackCharged";
	collisionController.initialize(JsonResource{ CollisionController::ActionJsonDir / "press.json" });
	guiTag = "AttackActionPress";
}

void AttackActionPress::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionPress::update() {
	BaseAttackAction::update();
}
