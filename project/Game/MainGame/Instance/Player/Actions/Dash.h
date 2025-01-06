#pragma once

#include "BaseAction.h"

#include <Library/Math/Vector3.h>

class Dash final : public BaseAction {
public:
	Dash();
	~Dash() = default;

public:
	bool triggered_key() const override;
	bool triggered_pad() const override;
	bool end_action() const override;
	bool bufferingabgle() const override;
	bool transitionable() const override;
	void reset() override;
	void update() override;

public:
	Vector3 moveFrom;
	Vector3 moveTo;
};
