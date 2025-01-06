#pragma once

#include "BaseAttackAction.h"

class AttackActionPress final : public BaseAttackAction {
public:
	AttackActionPress();
	~AttackActionPress() = default;

public:
	void reset() override;
	void update() override;
};
