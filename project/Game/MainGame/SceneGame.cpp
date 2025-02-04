#include "SceneGame.h"

#include <Engine/Debug/DebugValues/DebugValues.h>
#include <Engine/Module/Render/RenderNode/BaseRenderNode.h>
#include <Engine/Module/Render/RenderNode/Object3DNode/Object3DNode.h>
#include <Engine/Module/Render/RenderNode/SkinningMesh/SkinningMeshNode.h>
#include <Engine/Module/Render/RenderNode/Particle/ParticleBillboardNode/ParticleBillboardNode.h>
#include <Engine/Module/Render/RenderNode/Particle/ParticleMeshNode/ParticleMeshNode.h>
#include <Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Rendering/DirectX/DirectXSwapChain/DirectXSwapChain.h>
#include <Engine/Resources/Audio/AudioManager.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Utility/Tools/SmartPointer.h>
#include "Engine/Rendering/DirectX/DirectXResourceObject/ConstantBuffer/Material/Material.h"

#include <Engine/Resources/Animation/NodeAnimation/NodeAnimationManager.h>
#include <Engine/Resources/Animation/Skeleton/SkeletonManager.h>
#include <Engine/Resources/PolygonMesh/PolygonMeshManager.h>

#include "Game/MainGame/Instance/Player/CollisionController/CollisionController.h"
#include "Game/MainGame/Misc/GameCallback.h"

void SceneGame::load() {
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/skydome.gltf");
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/shadow.gltf");
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/Particle01.gltf");
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/HitParticle.gltf");
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	NodeAnimationManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	SkeletonManager::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	PolygonMeshManager::RegisterLoadQue("./Resources/Game/Models/Enemy.gltf");
	PolygonMeshManager::RegisterLoadQue("./EngineResources/Models/Collider/Sphere/SphereCollider.obj");
}

void SceneGame::initialize() {
	// Allocation
	player = eps::CreateUnique<Player>();

	Enemy::player = player;
	skydome = eps::CreateUnique<MeshInstance>("skydome.gltf");
	skydome->get_transform().set_scale(CVector3::BASIS * 100);
	skydome->get_materials()[0].lightType = LighingType::None;
	skydome->begin_rendering();
	playerShadow = eps::CreateUnique<MeshInstance>("shadow.gltf");
	// ---------- Managers ---------- 
	collisionManager = std::make_unique<CollisionManager>();
	auto callbackTemp = eps::CreateUnique<GameCallback>(player);
	enemyManager = eps::CreateUnique<EnemyManager>(collisionManager, callbackTemp);
	callback = callbackTemp;

	collisionManager->set_callback_manager(std::move(callbackTemp));
	CollisionController::collisionManager = collisionManager.get();


	// ---------- WorldInstances ---------- 

	// Camera
	camera3D = std::make_unique<FollowCamera>();
	camera3D->initialize();
	camera3D->set_transform({
		CVector3::BASIS,
		Quaternion::EulerDegree(45,0,0),
		{0,10,-10}
		});

	Particle::lookAtDefault = camera3D.get();
	HitAnimation::camera = camera3D;

	CollisionController::parent = player;
	player->initialize(camera3D);

	camera3D->set_target(player);

	//enemy = eps::CreateUnique<Enemy>(player);
	//collisionManager->register_collider("Enemy", enemy->get_collider());
	//callback->register_enemy(enemy);

	// Light
	directionalLight = eps::CreateUnique<DirectionalLightInstance>();

	// ---------- Rendering ---------- 
	auto meshNode = eps::CreateShared<Object3DNode>();
	meshNode->initialize();
	meshNode->set_config(
		RenderNodeConfig::ContinueDrawBefore | RenderNodeConfig::ContinueUseDpehtBefore);
	meshNode->set_render_target_SC(DirectXSwapChain::GetRenderTarget());

	auto skinningMeshNode = eps::CreateShared<SkinningMeshNode>();
	skinningMeshNode->initialize();
	skinningMeshNode->set_config(
		RenderNodeConfig::ContinueDrawBefore | RenderNodeConfig::ContinueUseDpehtBefore |
		RenderNodeConfig::ContinueDrawAfter | RenderNodeConfig::ContinueUseDpehtAfter
	);
	skinningMeshNode->set_render_target_SC(DirectXSwapChain::GetRenderTarget());

	auto particleNode = eps::CreateShared<ParticleMeshNode>();
	particleNode->initialize();
	particleNode->set_config(
		RenderNodeConfig::ContinueDrawBefore |
		RenderNodeConfig::ContinueDrawAfter | RenderNodeConfig::ContinueUseDpehtAfter
	);
	particleNode->set_render_target_SC(DirectXSwapChain::GetRenderTarget());

	renderPath = eps::CreateUnique<RenderPath>();
	renderPath->initialize({ meshNode, skinningMeshNode, particleNode });
}

void SceneGame::update() {
	player->begin();
	callback->begin();
	enemyManager->begin();
	camera3D->input();

	callback->update();
	player->update();
	enemyManager->update();
	camera3D->update();

	playerShadow->update();
	float scaleBase = 1 / (player->get_transform().get_translate().y + 2);
	playerShadow->get_transform().set_scale({ scaleBase, scaleBase, scaleBase });
	playerShadow->get_transform().set_translate(player->world_position());
	playerShadow->get_transform().set_translate_y(0.01f);
}

void SceneGame::begin_rendering() {
	camera3D->update_matrix();
	directionalLight->update_affine();
	callback->begin_rendering();
	player->begin_rendering();
	enemyManager->begin_rendering();
	playerShadow->begin_rendering();
}

void SceneGame::late_update() {
	collisionManager->update();
	collisionManager->collision("AttackCollider", "Enemy");

	player->late_update();
	enemyManager->late_update();
	//if (callback->is_reset()) {
	//	hitAnimationTimer = 0;
	//}
}

void SceneGame::draw() const {
	renderPath->begin();
	camera3D->register_world(1, 5);
	directionalLight->register_world(3);
	// Mesh
	enemyManager->draw();
	playerShadow->draw();
	skydome->draw();
	callback->draw_billboard();
	DebugValues::ShowGrid();
#ifdef _DEBUG
	camera3D->debug_draw();
	collisionManager->debug_draw3d();
#endif // _DEBUG

	renderPath->next();
	camera3D->register_world(1, 6);
	directionalLight->register_world(3);
	// AnimatedMesh
	player->draw();

	renderPath->next();
	camera3D->register_world(1);
	callback->draw_particle();

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
