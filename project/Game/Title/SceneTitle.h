#pragma once

#include <Engine/Runtime/Scene/BaseScene.h>

#include <Engine/Module/Render/RenderPath/RenderPath.h>

class SceneTitle final : public BaseScene {
public:
	void load() override;
	void initialize() override;
	void update() override;
	void draw() const override;

private:
	std::unique_ptr<RenderPath> renderPath;
};

