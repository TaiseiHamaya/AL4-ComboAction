#include "SceneClear.h"

#include <Library/Math/Transform2D.h>
#include <Library/Utility/Tools/SmartPointer.h>

#include <Engine/Application/EngineSettings.h>
#include <Engine/Assets/PolygonMesh/PolygonMeshLibrary.h>
#include <Engine/Assets/Texture/TextureLibrary.h>
#include <Engine/GraphicsAPI/DirectX/DXSwapChain/DXSwapChain.h>
#include <Engine/Module/Render/RenderNode/2D/Sprite/SpriteNode.h>
#include <Engine/Module/Render/RenderNode/BaseRenderNode.h>
#include <Engine/Module/Render/RenderNode/Forward/Mesh/StaticMeshNodeForward.h>
#include <Engine/Module/World/Camera/Camera2D.h>
#include <Engine/Runtime/Input/Input.h>
#include <Engine/Runtime/Scene/SceneManager.h>

#include <Game/SceneFactoryGame.h>

void SceneClear::load() {
	TextureLibrary::RegisterLoadQue("./Resources/control.png");
	TextureLibrary::RegisterLoadQue("./Resources/clear.png");
}

void SceneClear::initialize() {
	Camera2D::Initialize();
	
	clear = eps::CreateUnique<SpriteInstance>("clear.png", Vector2{ 0.5f, 0.5f });
	clear->get_transform().set_translate(EngineSettings::CLIENT_SIZE / 2 + Vector2{ 0, 128 });

	control = eps::CreateUnique<SpriteInstance>("control.png", Vector2{ 0.5f, 0.5f });
	control->get_transform().set_translate(EngineSettings::CLIENT_SIZE / 2 - Vector2{ 0, 128 });

	// Node&Path
	std::shared_ptr<StaticMeshNodeForward> object3dNode;
	object3dNode = std::make_unique<StaticMeshNodeForward>();
	object3dNode->initialize();
	object3dNode->set_render_target_SC(DxSwapChain::GetRenderTarget());

	std::shared_ptr<SpriteNode> spriteNode;
	spriteNode = std::make_unique<SpriteNode>();
	spriteNode->initialize();
	spriteNode->set_config(RenderNodeConfig::ContinueDrawAfter | RenderNodeConfig::ContinueDrawBefore);
	spriteNode->set_render_target_SC(DxSwapChain::GetRenderTarget());

	renderPath = eps::CreateUnique<RenderPath>();
	renderPath->initialize({ object3dNode,spriteNode });
}

void SceneClear::update() {
	if (Input::IsTriggerKey(KeyID::Space) || Input::IsTriggerPad(PadID::A)) {
		SceneManager::SetSceneChange(SceneList::Title, 1);
	}
	clear->begin_rendering();
	control->begin_rendering();
}

void SceneClear::draw() const {
	// メッシュ
	renderPath->begin();


	// Sprite
	renderPath->next();
	clear->draw();
	control->draw();

	renderPath->next();
}
