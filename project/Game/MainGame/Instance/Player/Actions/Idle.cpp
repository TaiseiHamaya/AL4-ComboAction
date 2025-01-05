#include "Idle.h"

#include "../Player.h"

#include <Engine/Runtime/Input/Input.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>

bool Idle::triggered() const {
	return true;
}

bool Idle::can_trigger_next() const {
	return yVelocity <= 6.0f;
}

void Idle::initialize() {
	timer = 0;
	inputWASD = CVector2::ZERO;
	xzVelocity = CVector2::ZERO;
	yVelocity = 0;
	forwardTo = player->get_transform().get_quaternion();
}

void Idle::update() {
	Transform3D& transform = player->get_transform();

	// ---------- ジャンプ処理 ----------
	if (transform.get_translate().y == 0 && Input::IsTriggerKey(KeyID::Space)) {
		yVelocity = 8.0f;
	}
	// 重力処理
	yVelocity += -20.0f * WorldClock::DeltaSeconds();

	// ---------- 水平方向のvelocity ----------
	// キー入力
	inputWASD = InputAdvanced::PressWASD();
	// velocity加算
	constexpr float SPEED{ 50.0f };
	xzVelocity += inputWASD * SPEED * WorldClock::DeltaSeconds();
	// 地面の上では摩擦減衰
	if (transform.get_translate().y == 0 && inputWASD.length() == 0) {
		xzVelocity *= 0.8f;
	}
	// 水平方向の速度の最大
	constexpr float MAX_SPEED{ 6.0f };
	if (xzVelocity.length() >= MAX_SPEED) {
		xzVelocity = xzVelocity.normalize() * MAX_SPEED;
	}

	// Velocityにまとめる
	Vector3 velocity = { xzVelocity.x, yVelocity, xzVelocity.y };
	// 移動
	transform.plus_translate(velocity * WorldClock::DeltaSeconds());
	// 地面に埋まらないようにする
	if (transform.get_translate().y <= 0.0f) {
		transform.set_translate_y(0.0f);
	}

	// ---------- 移動方向を向く ----------
	// 向く方向
	if (xzVelocity.length() != 0) {
		forwardTo = Quaternion::LookForward(Vector3{ xzVelocity.x, 0, xzVelocity.y }.normalize());
	}
	// Slerp補完
	if (inputWASD.length() != 0) {
		transform.set_quaternion(
			Quaternion::Slerp(transform.get_quaternion(), forwardTo, 0.1f)
		);
	}
}
