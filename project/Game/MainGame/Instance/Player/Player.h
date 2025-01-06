#pragma once

#include <Engine/Module/World/AnimatedMesh/AnimatedMeshInstance.h>

#include <memory>

#include "Actions/BaseAction.h"

class Player final : public AnimatedMeshInstance {
public:
	Player();
	~Player() = default;

public:
	void initialize();
	void begin();

	void update();

private:
	void set_action(BaseAction* action);

private:
	BaseAction* nowAction{ nullptr }; // 今のアクション
	BaseAction* actionBuffer{ nullptr }; // 先行入力保存用
	std::unique_ptr<BaseAction> rootAction; // Idle
};
