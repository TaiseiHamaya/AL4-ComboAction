#ifdef _DEBUG
#include "DebugScene.h"

#include <Engine/Runtime/Scene/SceneManager.h>

#include "Game/MainGame/SceneGame.h"
#include "Game/Title/SceneTitle.h"

#include <Engine/GraphicsAPI/DirectX/DXSwapChain/DXSwapChain.h>
#include <Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h>
#include <Engine/Module/Render/RenderNode/BaseRenderNode.h>
#include <Engine/Runtime/Input/Input.h>

void DebugScene::update() {
}

void DebugScene::draw() const {
	DxSwapChain::GetRenderTarget()->begin(eps::to_bitflag<RenderNodeConfig>(RenderNodeConfig::Default), nullptr);
}

#include <imgui.h>
void DebugScene::debug_update() {
	ImGui::Begin("SceneSelect");
	
	if (ImGui::Button("Title") || Input::IsPressKey(KeyID::F1)) {
		SceneManager::SetSceneChange(0, 0);
	}
	if (ImGui::Button("Game") || Input::IsPressKey(KeyID::F2)) {
		SceneManager::SetSceneChange(1, 0);
	}

	ImGui::End();
}
#endif // _DEBUG
