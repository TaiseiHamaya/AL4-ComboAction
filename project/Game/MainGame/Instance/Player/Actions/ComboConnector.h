#pragma once

#include "BaseAction.h"
#include "Dash.h"

#include <Engine/Runtime/Input/Input.h>

class ComboConnector final : public BaseAction {
public:
	ComboConnector() = default;
	template<class Under, class Over>
	ComboConnector(
		std::unique_ptr<Under> under,
		std::unique_ptr<Over> over,
		KeyID key_, PadID pad_, float branchTime_, bool cancelable_
	);
	~ComboConnector() = default;

public:
	bool triggered_key() const override;
	bool triggered_pad() const override;
	bool end_action() const override { return false; };
	bool bufferingabgle() const override { return true; };
	bool transitionable() const override { return true; };
	void reset() override;
	void update() override;
	BaseAction* next_combo_action() override;

private:
	float keyTimer{ 0 };
	float BranchTime;
	KeyID key;
	PadID pad;
	bool isReleased{ false };
	bool cancelable;
};

template<class Under, class Over>
inline ComboConnector::ComboConnector(std::unique_ptr<Under> under, std::unique_ptr<Over> over, KeyID key_, PadID pad_, float branchTime_, bool cancelable_) :
	key(key_),
	pad(pad_),
	BranchTime(branchTime_),
	cancelable(cancelable_) {
	useAnimationName = "Charge";
	actionTree.emplace_back(std::move(under));
	actionTree.emplace_back(std::move(over));
	if (cancelable) {
		actionTree.emplace_back(std::make_unique<Dash>());
	}
}

template<class Under, class Over>
std::unique_ptr<ComboConnector> CreateComboConnector(KeyID key, PadID pad, float branchTime, bool cancelable = true) {
	return std::make_unique<ComboConnector>(
		std::make_unique<Under>(), std::make_unique<Over>(), key, pad, branchTime, cancelable
	);
}
