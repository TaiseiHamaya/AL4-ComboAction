#pragma once

#include "BaseAction.h"

#include <Library/Math/Vector2.h>
#include <Library/Math/Quaternion.h>

class Idle final : public BaseAction {
public:
	bool triggered() const override;
	bool can_trigger_next() const override;
	void initialize() override;
	void update() override;

private:
	Vector2 inputWASD;
	Vector2 xzVelocity;
	float yVelocity;

	Quaternion forwardTo;
};
