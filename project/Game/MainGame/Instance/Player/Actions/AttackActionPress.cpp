#include "AttackActionPress.h"

AttackActionPress::AttackActionPress() {
	useAnimationName = "AttackCharged";
	bufferingableParametric = 1.0f;
	transitionableParametric = 1.0f;
	collisionController.initialize(JsonResource{ CollisionController::ActionJsonDir / "press.json" });
#ifdef _DEBUG
	guiTag = "AttackActionPress";
#endif // _DEBUG

}

void AttackActionPress::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionPress::update() {
	BaseAttackAction::update();
}
