#pragma once

#include <Engine/Runtime/Scene/BaseScene.h>

#include <memory>

#include <Engine/Module/Render/RenderPath/RenderPath.h>
#include <Engine/Module/World/Sprite/SpriteInstance.h>

class SceneTitle final : public BaseScene {
public:
	void load() override;
	void initialize() override;
	void update() override;
	void draw() const override;

private:
	std::unique_ptr<RenderPath> renderPath;

	std::unique_ptr<SpriteInstance> title;
	std::unique_ptr<SpriteInstance> control;
};

