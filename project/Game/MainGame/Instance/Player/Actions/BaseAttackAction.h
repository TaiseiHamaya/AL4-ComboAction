#pragma once

#include "BaseAction.h"

#include "../CollisionController/CollisionController.h"

class BaseAttackAction : public BaseAction {
public:
	BaseAttackAction() = default;
	~BaseAttackAction() = default;

public:
	bool triggered_key() const override;
	bool triggered_pad() const override;
	bool end_action() const override;
	bool bufferingabgle() const override;
	bool transitionable() const override;

	virtual void reset() override;
	virtual void update() override;

#ifdef _DEBUG
public:
	virtual void debug_gui();
protected:
	std::string guiTag;
#endif // _DEBUG

protected:
	CollisionController collisionController;
	float bufferingableParametric{ 0 };
	float transitionableParametric{ 0 };
};

