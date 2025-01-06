#include "AttackActionPress.h"

AttackActionPress::AttackActionPress() {
	useAnimationName = "AttackCharged";
}

void AttackActionPress::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionPress::update() {
	BaseAttackAction::update();
}
