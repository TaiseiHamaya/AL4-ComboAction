#include "SceneGame.h"

#include <Engine/Debug/DebugValues/DebugValues.h>
#include <Engine/Module/Render/RenderNode/BaseRenderNode.h>
#include <Engine/Module/Render/RenderNode/Object3DNode/Object3DNode.h>
#include <Engine/Module/Render/RenderNode/SkinningMesh/SkinningMeshNode.h>
#include <Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h>
#include <Engine/Rendering/DirectX/DirectXSwapChain/DirectXSwapChain.h>
#include <Engine/Resources/Audio/AudioManager.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Utility/Tools/SmartPointer.h>

#include <Engine/Resources/Animation/NodeAnimation/NodeAnimationManager.h>
#include <Engine/Resources/Animation/Skeleton/SkeletonManager.h>
#include <Engine/Resources/PolygonMesh/PolygonMeshManager.h>

void SceneGame::load() {
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	NodeAnimationManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	SkeletonManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
}

void SceneGame::initialize() {
	// ---------- Managers ---------- 
	collisionManager = std::make_unique<CollisionManager>();

	// ---------- WorldInstances ---------- 

	// Camera
	camera3D = std::make_unique<Camera3D>();
	camera3D->initialize();
	camera3D->set_transform({
		CVector3::BASIS,
		Quaternion::EulerDegree(45,0,0),
		{0,10,-10}
		});

	player = eps::CreateUnique<Player>();

	// Light
	directionalLight = eps::CreateUnique<DirectionalLightInstance>();

	// ---------- Rendering ---------- 
	auto meshNode = eps::CreateShared<Object3DNode>();
	meshNode->initialize();
	meshNode->set_config(
		eps::to_bitflag(RenderNodeConfig::ContinueDrawBefore) | RenderNodeConfig::ContinueUseDpehtBefore);
	meshNode->set_render_target_SC(DirectXSwapChain::GetRenderTarget());

	auto skinningMeshNode = eps::CreateShared<SkinningMeshNode>();
	skinningMeshNode->initialize();
	skinningMeshNode->set_config(
		eps::to_bitflag(RenderNodeConfig::ContinueDrawAfter) | RenderNodeConfig::ContinueUseDpehtAfter
	);
	skinningMeshNode->set_render_target_SC(DirectXSwapChain::GetRenderTarget());

	renderPath = eps::CreateUnique<RenderPath>();
	renderPath->initialize({ meshNode, skinningMeshNode });
}

void SceneGame::update() {
	player->begin();

	player->update();

}

void SceneGame::begin_rendering() {
	camera3D->update_matrix();
	directionalLight->update_matrix();
	player->begin_rendering();

	player->late_update();
}

void SceneGame::draw() const {
	renderPath->begin();
	camera3D->register_world(1);
	directionalLight->register_world(3);
	// Mesh
#ifdef _DEBUG
	DebugValues::ShowGrid();
	camera3D->debug_draw();
#endif // _DEBUG

	renderPath->next();
	camera3D->register_world(1);
	directionalLight->register_world(3);
	// AnimatedMesh
	player->draw();

	renderPath->next();
}

#ifdef _DEBUG

void SceneGame::debug_update() {

	AudioManager::DebugGui();

	ImGui::Begin("WorldClock");
	WorldClock::DebugGui();
	ImGui::End();

	ImGui::Begin("CollisionManager");
	collisionManager->debug_gui();
	ImGui::End();

	ImGui::Begin("Camera3D");
	camera3D->debug_gui();
	ImGui::End();

	ImGui::Begin("DirectionalLight");
	directionalLight->debug_gui();
	ImGui::End();

	ImGui::Begin("Player");
	player->debug_gui();
	ImGui::End();
}
#endif // _DEBUG
