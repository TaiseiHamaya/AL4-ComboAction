#pragma once

#include "BaseAction.h"

#include <Library/Math/Vector3.h>

class Dash final : public BaseAction {
public:
	bool triggered() const override;
	bool can_trigger_next() const override;
	void initialize() override;
	void update() override;

public:
	Vector3 moveFrom;
	Vector3 moveTo;
};
