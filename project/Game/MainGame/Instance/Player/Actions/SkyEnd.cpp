#include "SkyEnd.h"

#include "../Player.h"

#include <Engine/Assets/Animation/NodeAnimation/NodeAnimationPlayer.h>

SkyEnd::SkyEnd() {
	useAnimationName = "SkyEnd";
}

bool SkyEnd::triggered_key() const {
	return false;
}

bool SkyEnd::triggered_pad() const {
	return false;
}

bool SkyEnd::end_action() const {
	NodeAnimationPlayer* animation = player->get_animation();
	if (animation) {
		return animation->is_end();
	}
	return true;
}

bool SkyEnd::bufferingabgle() const {
	return false;
}

bool SkyEnd::transitionable() const {
	return false;
}

void SkyEnd::reset() {
	timer = 0;
}

void SkyEnd::update() {
}
