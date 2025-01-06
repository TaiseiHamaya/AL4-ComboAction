#include "BaseAction.h"

#include "../Player.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Resources/Animation/NodeAnimation/NodeAnimationPlayer.h>

void BaseAction::set_player(Player* const player_) {
	player = player_;
	for (auto& action : actionTree) {
		action->set_player(player);
	}
}

void BaseAction::reset_animation() {
	NodeAnimationPlayer* animation = player->get_animation();
	animation->reset_animation(useAnimationName);
	animation->restart();
}

void BaseAction::begin() {
	timer += WorldClock::DeltaSeconds();
}

BaseAction* BaseAction::next_combo_action() {
	for (auto& action : actionTree) {
		if (action->triggered_key()) {
			return action.get();
		}
	}
	return nullptr;
}
