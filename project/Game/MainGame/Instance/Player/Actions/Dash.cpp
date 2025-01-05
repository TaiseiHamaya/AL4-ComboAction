#include "Dash.h"

#include "../Player.h"

#include <Engine/Runtime/Input/Input.h>

constexpr float MOVE_TIME{ 0.5f };

bool Dash::triggered() const {
	return Input::IsTriggerKey(KeyID::LShift);
}

bool Dash::can_trigger_next() const {
	return timer >= MOVE_TIME;
}

void Dash::initialize() {
	timer = 0;
	Transform3D& transform = player->get_transform();
	constexpr float MOVE_DISTANCE{ 5.0f };
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
