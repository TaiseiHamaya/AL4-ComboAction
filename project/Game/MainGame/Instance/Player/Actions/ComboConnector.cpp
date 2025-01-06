#include "ComboConnector.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>

bool ComboConnector::triggered_key() const {
	return Input::IsTriggerKey(key);
}

bool ComboConnector::triggered_pad() const {
	return Input::IsTriggerPad(pad);
}

void ComboConnector::reset() {
	timer = 0;
	keyTimer = 0;
	isReleased = false;
}

void ComboConnector::update() {
	if (Input::IsPressKey(key) || Input::IsPressPad(pad)) {
		keyTimer += WorldClock::DeltaSeconds();
	}
	else {
		isReleased = true;
	}
}

BaseAction* ComboConnector::next_combo_action() {
	if (isReleased) {
		if (keyTimer <= BranchTime) {
			return actionTree[0].get();
		}
		else {
			return actionTree[1].get();
		}
	}
	else if (cancelable) {
		if (actionTree[2]->triggered_key() || actionTree[2]->triggered_pad()) {
			return actionTree[2].get();
		}
	}
	return nullptr;
}
