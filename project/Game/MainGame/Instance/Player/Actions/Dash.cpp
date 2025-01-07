#include "Dash.h"

#include "../Player.h"

#include <Engine/Runtime/Input/Input.h>

constexpr float MOVE_TIME{ 0.5f };

Dash::Dash() {
	useAnimationName = "Dash";
}

bool Dash::triggered_key() const {
	return Input::IsTriggerKey(KeyID::LShift);
}

bool Dash::triggered_pad() const {
	return Input::IsTriggerPad(PadID::LShoulder);
}

bool Dash::end_action() const {
	return timer >= MOVE_TIME;
}

bool Dash::bufferingabgle() const {
	return timer >= MOVE_TIME * 0.9f;
}

bool Dash::transitionable() const {
	return timer >= MOVE_TIME;
}

void Dash::reset() {
	timer = 0;
	Transform3D& transform = player->get_transform();
	constexpr float MOVE_DISTANCE{ 10.0f };
	moveFrom = player->world_position();
	moveTo = player->world_position() +
		CVector3::BASIS_Z * MOVE_DISTANCE * transform.get_quaternion();
}

void Dash::update() {
	float parametric = timer / MOVE_TIME;
	player->get_transform().set_translate(
		Vector3::Lerp(moveFrom, moveTo, (parametric))
	);
}
