#include "Player.h"

#include "Actions/Idle.h"

Player::Player() :
	AnimatedMeshInstance("Player.gltf") {
}

void Player::initialize() {
	rootAction = std::make_unique<Idle>();
	rootAction->set_player(this);
	set_action(rootAction.get());
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

	// 先行入力なしで終了した場合リセット
	if (nowAction->end_action()) {
		set_action(rootAction.get());
	}
	// 先行入力可能かつまだ先行入力してない場合
	// 先行入力が存在するかチェック
	if (nowAction->bufferingabgle() && !actionBuffer) {
		actionBuffer = nowAction->next_combo_action();
	}
	// 遷移可能な場合は遷移
	if (nowAction->transitionable() && actionBuffer) {
		set_action(actionBuffer);
		// 先行入力を削除
		actionBuffer = nullptr;
	}
}

void Player::set_action(BaseAction* action) {
	nowAction = action;
	nowAction->reset();
	nowAction->reset_animation();
}
