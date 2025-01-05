#include "BaseAction.h"

#include <Engine/Runtime/WorldClock/WorldClock.h>

void BaseAction::set_player(Player* const player_) {
	player = player_;
}

void BaseAction::begin() {
	timer += WorldClock::DeltaSeconds();
}
