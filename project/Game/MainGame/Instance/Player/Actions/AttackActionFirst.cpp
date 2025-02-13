#include "AttackActionFirst.h"

#include "ComboConnector.h"
#include "AttackActionSecond.h"
#include "AttackActionPress.h"

#include <Engine/Runtime/Input/Input.h>

AttackActionFirst::AttackActionFirst() {
	useAnimationName = "AttackFirst";
	bufferingableParametric = 0.3f;
	transitionableParametric = 0.9f;
	actionTree.emplace_back(CreateComboConnector<AttackActionSecond, AttackActionPress>(KeyID::K, PadID::X, 0.6f));
	collisionController.initialize(JsonAsset{ CollisionController::ActionJsonDir / "first.json" });
#ifdef _DEBUG
	guiTag = "AttackActionFirst";
#endif // _DEBUG

}

void AttackActionFirst::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionFirst::update() {
	BaseAttackAction::update();
}
