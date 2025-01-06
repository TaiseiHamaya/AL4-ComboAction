#pragma once

#include "BaseAttackAction.h"

class AttackActionSecond final : public BaseAttackAction {
public:
	AttackActionSecond();
	~AttackActionSecond() = default;

public:
	void reset() override;
	void update() override;
};
