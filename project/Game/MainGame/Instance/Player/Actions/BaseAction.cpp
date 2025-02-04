#include "BaseAction.h"

#include "../Player.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Assets/Animation/NodeAnimation/NodeAnimationPlayer.h>

void BaseAction::set_player(Reference<Player> player_) {
	player = player_;
	for (auto& action : actionTree) {
		action->set_player(player);
	}
}

void BaseAction::reset_animation() {
	NodeAnimationPlayer* animation = player->get_animation();
	animation->reset_animation(useAnimationName);
	animation->restart();
	animation->set_loop(loopAnimation);
}

void BaseAction::begin() {
	timer += WorldClock::DeltaSeconds();
}

BaseAction* BaseAction::next_combo_action() {
	for (auto& action : actionTree) {
		if (action->triggered_key() || action->triggered_pad()) {
			return action.get();
		}
	}
	return nullptr;
}

#ifdef _DEBUG


void BaseAction::debug_gui() {
	for (auto& action : actionTree) {
		action->debug_gui();
	}
}
#endif // _DEBUG
