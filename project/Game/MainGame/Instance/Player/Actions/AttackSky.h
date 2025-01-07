#pragma once

#include "BaseAttackAction.h"

class AttackSky final : public BaseAttackAction {
public:
	AttackSky();
	~AttackSky() = default;

public:
	void reset() override;
	void update() override;

	BaseAction* next_combo_action() override;
};

