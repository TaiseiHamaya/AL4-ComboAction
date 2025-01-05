#pragma once

#include <Engine/Runtime/Scene/BaseScene.h>

class SceneTitle final : public BaseScene {
public:
	void update() override;
	void draw() const override;
};

