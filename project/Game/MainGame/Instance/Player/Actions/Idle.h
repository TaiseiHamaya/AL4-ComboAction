#pragma once

#include "BaseAction.h"

#include <Library/Math/Vector2.h>
#include <Library/Math/Quaternion.h>

class WorldInstance;

class Idle final : public BaseAction {
public:
	Idle(Reference<const WorldInstance> camera_);
	~Idle() = default;

public:
	bool triggered_key() const override;
	bool triggered_pad() const override;
	bool bufferingabgle() const override;
	bool transitionable() const override;
	bool end_action() const;
	void reset() override;
	void update() override;

private:
	Vector2 inputWASD;
	Vector2 xzVelocity;
	float yVelocity{ 0 };

	Quaternion forwardTo;

	Reference<const WorldInstance> camera;
};
