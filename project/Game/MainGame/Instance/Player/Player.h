#pragma once

#include <Engine/Module/World/AnimatedMesh/AnimatedMeshInstance.h>

#include <vector>
#include <memory>

#include "Actions/BaseAction.h"

class Player final : public AnimatedMeshInstance {
public:
	Player();
	~Player() = default;

public:
	void begin();

	void update();

private:
	void set_action(uint32_t index);

	void triggers();

private:
	BaseAction* nowAction{ nullptr };
	std::vector<std::unique_ptr<BaseAction>> actions;
};
