#include "HitAnimation.h"

#include <Library/Utility/Tools/SmartPointer.h>

#include <Engine/GraphicsAPI/DirectX/DxResource/ConstantBuffer/Material/Material.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>
#include <Engine/Module/World/WorldManager.h>

HitAnimation::HitAnimation(Vector3&& position) {
	emitter = worldManager->create<ParticleEmitterInstance>(nullptr, false, "./Resources/Game/Json/Particles.json", 128);

	hitBillboard = worldManager->create<Billboard>(nullptr, false, "HitParticle.gltf");
	hitBillboard->get_materials()[0].lightingType = LighingType::None;

	emitter->get_transform().set_translate(position);
	emitter->emit();

	const Quaternion rotation = camera->get_transform().get_quaternion();
	hitBillboard->get_transform().set_translate(position + -CVector3::BASIS_Z * rotation);
	hitAnimationTimer = 0;
}

void HitAnimation::begin() {
	hitAnimationTimer += WorldClock::DeltaSeconds();
	hitBillboard->begin();
}

void HitAnimation::update() {
	hitBillboard->update();
	emitter->update();

	int currentFrame = static_cast<int>(std::floor(hitAnimationTimer / 0.0400f));
	hitBillboard->get_materials()[0].uvTransform.set_translate(
		{ std::min(currentFrame, 5) / 6.0f, 0 }
	);
}

void HitAnimation::transfer() {
	hitBillboard->transfer();
	emitter->transfer();
}

void HitAnimation::draw_billboard() const {
	hitBillboard->draw();
}

void HitAnimation::draw_particle() const {
	emitter->draw();
}

bool HitAnimation::is_end() const {
	return emitter->is_end_all() && hitAnimationTimer >= 0.5f;
}

Billboard::Billboard(std::string name) :
	StaticMeshInstance(name) {
}

void Billboard::fixed_update() {
	look_at(*camera.ptr());
}
