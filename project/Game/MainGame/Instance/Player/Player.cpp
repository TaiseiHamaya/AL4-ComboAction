#include "Player.h"

#include "Actions/Idle.h"
#include "Actions/Dash.h"

Player::Player() :
	AnimatedMeshInstance("Player.gltf", "Armatureアクション") {
	actions.emplace_back(std::make_unique<Idle>());
	actions.emplace_back(std::make_unique<Dash>());

	for (auto& action : actions) {
		action->set_player(this);
	}

	set_action(0);
}

void Player::begin() {
	AnimatedMeshInstance::begin();
	if (!nowAction) {
		set_action(0);
	}

	nowAction->begin();
}

void Player::update() {
	nowAction->update();

	if (nowAction->can_trigger_next()) {
		triggers();
	}
}

void Player::set_action(uint32_t index) {
	if (index < actions.size()) {
		nowAction = actions[index].get();
		nowAction->initialize();
	}
}

void Player::triggers() {
	for (uint32_t i = 0; auto & action : actions) {
		if (action.get() == nowAction) {
			++i;
			continue;
		}
		if (action->triggered()) {
			set_action(i);
			break;
		}
		++i;
	}
}
