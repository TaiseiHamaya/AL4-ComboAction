#pragma once

class Player;

#include <vector>
#include <memory>
#include <string>

class BaseAction {
public:
	BaseAction() = default;
	virtual ~BaseAction() = default;

public:
	void set_player(Player* const player);
	void reset_animation();
	void begin();
	virtual bool triggered_key() const = 0;
	virtual bool triggered_pad() const = 0;
	virtual bool bufferingabgle() const = 0;
	virtual bool end_action() const = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual bool transitionable() const = 0;
	virtual BaseAction* next_combo_action();

protected:
	float timer{ 0 };
	Player* player{ nullptr };
	std::string useAnimationName{ "Armatureアクション" };

	std::vector<std::unique_ptr<BaseAction>> actionTree;
};
