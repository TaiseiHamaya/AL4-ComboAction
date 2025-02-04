#include "AttackSky.h"

#include "../Player.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>

#include "SkyEnd.h"

AttackSky::AttackSky() {
	useAnimationName = "AttackSky";
	bufferingableParametric = 0.0f;
	transitionableParametric = 0.0f;
	loopAnimation = false;
	collisionController.initialize(JsonAsset{ CollisionController::ActionJsonDir / "sky.json" });

	actionTree.emplace_back(std::make_unique<SkyEnd>());
#ifdef _DEBUG
	guiTag = "AttackSky";
#endif // _DEBUG
}

void AttackSky::reset() {
	BaseAttackAction::reset();
	timer = 0;
}

void AttackSky::update() {
	BaseAttackAction::update();
	if (timer >= 0.166) {
		Vector3 down = Vector3{ 0,-15,0 };
		player->get_transform().plus_translate(down * WorldClock::DeltaSeconds());
	}
	if (player->get_transform().get_translate().y <= 0) {
		player->get_transform().set_translate_y(0.0f);
	}
}

BaseAction* AttackSky::next_combo_action() {
	if (player->get_transform().get_translate().y <= 0) {
		collisionController.disable_force();
		return actionTree[0].get();
	}
	return nullptr;
}
