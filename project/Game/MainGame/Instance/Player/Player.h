#pragma once

#include <Engine/Module/World/Mesh/SkinningMeshInstance.h>
#include <Library/Utility/Template/Reference.h>

#include <memory>

#include "Actions/BaseAction.h"

class Player final : public SkinningMeshInstance {
public:
	Player();
	~Player() = default;

public:
	void initialize(Reference<const WorldInstance> camera);
	void begin();

	void update();

#ifdef _DEBUG
public:
	void debug_gui() override;
#endif // _DEBUG

private:
	void set_action(BaseAction* action);

private:
	BaseAction* nowAction{ nullptr }; // 今のアクション
	BaseAction* actionBuffer{ nullptr }; // 先行入力保存用
	std::unique_ptr<BaseAction> rootAction; // Idle
};
