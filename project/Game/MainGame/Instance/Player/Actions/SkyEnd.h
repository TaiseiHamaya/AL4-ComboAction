#pragma once

#include "BaseAction.h"

class SkyEnd final : public BaseAction {
public:
	SkyEnd();
	~SkyEnd() = default;

public:
	bool triggered_key() const override;
	bool triggered_pad() const override;
	bool end_action() const override;
	bool bufferingabgle() const override;
	bool transitionable() const override;
	void reset() override;
	void update() override;
};

