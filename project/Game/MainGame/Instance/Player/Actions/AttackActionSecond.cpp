#include "AttackActionSecond.h"

#include "../Player.h"

#include "AttackSky.h"

AttackActionSecond::AttackActionSecond() {
	useAnimationName = "AttackSecond";
	bufferingableParametric = 0.5f;
	transitionableParametric= 0.9f;

	collisionController.initialize(JsonAsset{ CollisionController::ActionJsonDir / "second.json" });

	actionTree.emplace_back(std::make_unique<AttackSky>());
#ifdef _DEBUG
	guiTag = "AttackActionSecond";
#endif // _DEBUG
}

void AttackActionSecond::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackActionSecond::update() {
	BaseAttackAction::update();
}

BaseAction* AttackActionSecond::next_combo_action() {
	auto& attack = actionTree[0];

	if (attack->triggered_key() || attack->triggered_pad()) {
		if (player->get_transform().get_translate().y > 0) {
			collisionController.disable_force();
			return attack.get();
		}
	}

	return nullptr;
}
