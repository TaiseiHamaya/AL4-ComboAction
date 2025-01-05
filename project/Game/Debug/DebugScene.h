#pragma once
#ifdef _DEBUG

#include <Engine/Runtime/Scene/BaseScene.h>

class DebugScene final : public BaseScene {

public:
	void update() override;
	void draw() const override;

public:
	void debug_update() override;
};
#endif // _DEBUG
