#include "SceneTitle.h"

#include "Engine/Rendering/DirectX/DirectXSwapChain/DirectXSwapChain.h"
#include "Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h"
#include "Engine/Module/Render/RenderNode/BaseRenderNode.h"

void SceneTitle::update() {
}

void SceneTitle::draw() const {
	DirectXSwapChain::GetRenderTarget()->begin(eps::to_bitflag<RenderNodeConfig>(RenderNodeConfig::Default), nullptr);
}
