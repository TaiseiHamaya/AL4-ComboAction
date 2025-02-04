#include "SceneTitle.h"

#include "Engine/GraphicsAPI/DirectX/DXSwapChain/DXSwapChain.h"
#include "Engine/Module/Render/RenderTargetGroup/SwapChainRenderTargetGroup.h"
#include "Engine/Module/Render/RenderNode/BaseRenderNode.h"

void SceneTitle::update() {
}

void SceneTitle::draw() const {
	DxSwapChain::GetRenderTarget()->begin(eps::to_bitflag<RenderNodeConfig>(RenderNodeConfig::Default), nullptr);
}
