#pragma once

class Player;

class BaseAction {
public:
	BaseAction() = default;
	virtual ~BaseAction() = default;

public:
	void set_player(Player* const player);
	void begin();
	virtual bool triggered() const = 0;
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual bool can_trigger_next() const = 0;

protected:
	float timer{ 0 };
	Player* player{ nullptr };
};
