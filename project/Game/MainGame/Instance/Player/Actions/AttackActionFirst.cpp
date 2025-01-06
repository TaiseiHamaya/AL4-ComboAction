#include "AttackActionFirst.h"

#include "ComboConnector.h"
#include "AttackActionSecond.h"
#include "AttackActionPress.h"

#include <Engine/Runtime/Input/Input.h>

AttackActionFirst::AttackActionFirst() {
	useAnimationName = "AttackFirst";
	bufferingableParametric = 0.3f;
	transitionableParametric = 0.9f;
	actionTree.emplace_back(CreateComboConnector<AttackActionSecond, AttackActionPress>(KeyID::K, PadID::A, 0.6f));
}

void AttackActionFirst::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionFirst::update() {
	BaseAttackAction::update();
}
