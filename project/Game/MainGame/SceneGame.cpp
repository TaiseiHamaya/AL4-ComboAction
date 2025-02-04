#include "SceneGame.h"

#include <Library/Utility/Tools/SmartPointer.h>

#include <Engine/Assets/Animation/NodeAnimation/NodeAnimationLibrary.h>
#include <Engine/Assets/Animation/Skeleton/SkeletonLibrary.h>
#include <Engine/Assets/Audio/AudioLibrary.h>
#include <Engine/Assets/PolygonMesh/PolygonMeshLibrary.h>
#include <Engine/Debug/DebugValues/DebugValues.h>
#include <Engine/GraphicsAPI/DirectX/DxResource/ConstantBuffer/Material/Material.h>
#include <Engine/GraphicsAPI/DirectX/DXSwapChain/DXSwapChain.h>
#include <Engine/Module/Render/RenderNode/BaseRenderNode.h>
#include <Engine/Module/Render/RenderNode/Deferred/Lighting/DirectionalLighingNode.h>
#include <Engine/Module/Render/RenderNode/Deferred/Mesh/SkinningMeshNodeDeferred.h>
#include <Engine/Module/Render/RenderNode/Deferred/Mesh/StaticMeshNodeDeferred.h>
#include <Engine/Module/Render/RenderNode/Forward/Particle/ParticleBillboardNode/ParticleBillboardNode.h>
#include <Engine/Module/Render/RenderNode/Forward/Particle/ParticleMeshNode/ParticleMeshNode.h>
#include <Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h>
#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Runtime/Scene/SceneManager.h>

#include <Game/SceneFactoryGame.h>
#include "Game/MainGame/Instance/Player/CollisionController/CollisionController.h"
#include "Game/MainGame/Misc/GameCallback.h"
#include <Engine/Module/Render/RenderNode/Debug/PrimitiveLine/PrimitiveLineNode.h>

#include "Game/MainGame/Instance/Player/Actions/AttackSky.h"

void SceneGame::load() {
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/skydome.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/shadow.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/Particle01.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/HitParticle.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	NodeAnimationLibrary::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	SkeletonLibrary::RegisterLoadQue("./Resources/Game/Models/Player.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Resources/Game/Models/Enemy.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./EngineResources/Models/Collider/Sphere/SphereCollider.obj");
}

void SceneGame::initialize() {
	worldManager = eps::CreateUnique<WorldManager>();
	CollisionController::worldManager = worldManager;
	HitAnimation::worldManager = worldManager;
	// Allocation
	player = worldManager->create<Player>();

	Enemy::player = player;
	skydome = worldManager->create<StaticMeshInstance>(nullptr, false, "skydome.gltf");
	skydome->get_transform().set_scale(CVector3::BASIS * 100);
	skydome->get_materials()[0].lightingType = LighingType::None;
	playerShadow = worldManager->create<StaticMeshInstance>(nullptr, false, "shadow.gltf");
	// ---------- Managers ---------- 
	collisionManager = std::make_unique<CollisionManager>();
	auto callbackTemp = eps::CreateUnique<GameCallback>(player);
	enemyManager = eps::CreateUnique<EnemyManager>(collisionManager, callbackTemp, worldManager);
	callback = callbackTemp;

	collisionManager->set_callback_manager(std::move(callbackTemp));
	CollisionController::collisionManager = collisionManager;

	directionalLightingExecutor = eps::CreateUnique<DirectionalLightingExecutor>(1);

	// ---------- WorldInstances ---------- 

	// Camera
	camera3D = worldManager->create<FollowCamera>();
	camera3D->initialize();
	camera3D->set_transform({
		CVector3::BASIS,
		Quaternion::EulerDegree(45,0,0),
		{0,10,-10}
		});

	Particle::lookAtDefault = camera3D.get();
	HitAnimation::camera = camera3D;
	Billboard::camera = camera3D;
	AttackSky::camera = camera3D;

	CollisionController::parent = player;
	player->initialize(camera3D);

	camera3D->set_target(player);

	// Light
	directionalLight = worldManager->create<DirectionalLightInstance>();

	// ---------- Rendering ---------- 
	auto deferredRenderTarget = DeferredAdaptor::CreateGBufferRenderTarget();

	auto deferredMeshNode = eps::CreateShared<StaticMeshNodeDeferred>();
	deferredMeshNode->initialize();
	deferredMeshNode->set_render_target(deferredRenderTarget);
	deferredMeshNode->set_config(RenderNodeConfig::ContinueDrawBefore | RenderNodeConfig::ContinueUseDpehtBefore);

	auto skinMeshNodeDeferred = eps::CreateShared<SkinningMeshNodeDeferred>();
	skinMeshNodeDeferred->initialize();
	skinMeshNodeDeferred->set_render_target(deferredRenderTarget);
	skinMeshNodeDeferred->set_config(RenderNodeConfig::ContinueDrawAfter | RenderNodeConfig::ContinueUseDpehtAfter);

	auto directionalLightingNode = eps::CreateShared<DirectionalLightingNode>();
	directionalLightingNode->initialize();
	directionalLightingNode->set_render_target_SC(DxSwapChain::GetRenderTarget());
	directionalLightingNode->set_gbuffers(deferredRenderTarget);

	auto particleNode = eps::CreateShared<ParticleMeshNode>();
	particleNode->initialize();
	particleNode->set_config(
		RenderNodeConfig::NoClearDepth | RenderNodeConfig::ContinueDrawAfter
	);
	particleNode->set_render_target_SC(DxSwapChain::GetRenderTarget());

#ifdef _DEBUG
	std::shared_ptr<PrimitiveLineNode> primitiveLineNode;
	primitiveLineNode = std::make_unique<PrimitiveLineNode>();
	primitiveLineNode->initialize();
#endif // _DEBUG

	renderPath = eps::CreateUnique<RenderPath>();
#ifdef _DEBUG
	renderPath->initialize({ deferredMeshNode,skinMeshNodeDeferred ,directionalLightingNode,particleNode,primitiveLineNode });
#else
	renderPath->initialize({ deferredMeshNode,skinMeshNodeDeferred ,directionalLightingNode,particleNode });
#endif // _DEBUG
}

void SceneGame::update() {
	if (enemyManager->is_hitstop()) {
		callback->begin();
		callback->update();
		enemyManager->begin();
		return;
	}
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


	if (enemyManager->is_clear()) {
		SceneManager::SetSceneChange(SceneList::Claer, 1);
	}
}

void SceneGame::begin_rendering() {
	worldManager->update_matrix();

	camera3D->transfer();
	directionalLightingExecutor->write_to_buffer(0, directionalLight->light_data());
	callback->transfer();
	player->transfer();
	enemyManager->transfer();
	playerShadow->transfer();
}

void SceneGame::late_update() {
	collisionManager->update();
	if (enemyManager->is_hitstop()) {
		return;
	}
	collisionManager->collision("AttackCollider", "Enemy");
	collisionManager->collision("Enemy", "Enemy");

	player->late_update();
	enemyManager->late_update();
}

void SceneGame::draw() const {
	renderPath->begin();
	camera3D->register_world_projection(1);
	// StaticMesh
	enemyManager->draw();
	playerShadow->draw();
	skydome->draw();
	callback->draw_billboard();
	DebugValues::ShowGrid();
#ifdef _DEBUG
	camera3D->debug_draw_axis();
#endif // _DEBUG

	renderPath->next();
	camera3D->register_world_projection(1);
	// SkinningMesh
	player->draw();

	renderPath->next();
	camera3D->register_world_lighting(1);
	directionalLightingExecutor->draw_command(1);

	renderPath->next();
	camera3D->register_world_projection(1);
	callback->draw_particle();

	renderPath->next();

#ifdef _DEBUG
	camera3D->register_world_projection(1);
	collisionManager->debug_draw3d();
	camera3D->debug_draw_frustum();

	renderPath->next();
#endif // _DEBUG
}

#ifdef _DEBUG

void SceneGame::debug_update() {

	AudioLibrary::DebugGui();

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
