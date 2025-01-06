#pragma once

#include "BaseAttackAction.h"

class AttackActionFirst final : public BaseAttackAction {
public:
	AttackActionFirst();
	~AttackActionFirst() = default;

public:
	void reset() override;
	void update() override;
};
