#include "BaseAttackAction.h"

#include "../Player.h"

#include <Engine/Runtime/Input/Input.h>
#include <Engine/Resources/Animation/NodeAnimation/NodeAnimationPlayer.h>

bool BaseAttackAction::triggered_key() const {
	return Input::IsTriggerKey(KeyID::K);
}

bool BaseAttackAction::triggered_pad() const {
	return Input::IsTriggerPad(PadID::A);
}

bool BaseAttackAction::end_action() const {
	NodeAnimationPlayer* animation = player->get_animation();
	if (animation) {
		return animation->is_end();
	}
	return true;
}

bool BaseAttackAction::bufferingabgle() const {
	NodeAnimationPlayer* animation = player->get_animation();
	if (animation) {
		return animation->parametric() >= bufferingableParametric;
	}
	return true;
}

bool BaseAttackAction::transitionable() const {
	NodeAnimationPlayer* animation = player->get_animation();
	if (animation) {
		return animation->parametric() >= transitionableParametric;
	}
	return true;
}

void BaseAttackAction::reset() {
	collisionController.reset();
}

void BaseAttackAction::update() {
	collisionController.update();
	if (transitionable()) {
		collisionController.disable_force();
	}
}

#ifdef _DEBUG
#include <imgui.h>
void BaseAttackAction::debug_gui() {
	ImGui::Begin(guiTag.c_str());
	collisionController.debug_gui();
	ImGui::End();

	BaseAction::debug_gui();
}
#endif // _DEBUG
