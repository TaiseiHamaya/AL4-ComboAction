#include "HitAnimation.h"

#include <Engine/Utility/Tools/SmartPointer.h>

#include <Engine/Rendering/DirectX/DirectXResourceObject/ConstantBuffer/Material/Material.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>

HitAnimation::HitAnimation(Vector3&& position) {
	emitter = eps::CreateUnique<ParticleEmitterInstance>("./Resources/Game/Json/Particles.json", 128);

	hitBillboard = eps::CreateUnique<MeshInstance>("HitParticle.gltf");
	hitBillboard->get_materials()[0].lightType = LighingType::None;

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

void HitAnimation::begin_rendering() {
	hitBillboard->look_at(*camera.ptr());
	hitBillboard->begin_rendering();
	emitter->begin_rendering();
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
