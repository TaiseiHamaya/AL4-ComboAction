#pragma once

#include <Engine/Module/World/Mesh/MeshInstance.h>
#include <Engine/Module/World/Particle/ParticleEmitterInstance.h>

class HitAnimation final {
public:
	HitAnimation(Vector3&& position);
	~HitAnimation() = default;

	__NON_COPYABLE_CLASS(HitAnimation)

public:
	void begin();
	void update();
	void begin_rendering();
	void draw_billboard() const;
	void draw_particle() const;
	
public:
	bool is_end() const;

private:
	std::unique_ptr<MeshInstance> hitBillboard;
	std::unique_ptr<ParticleEmitterInstance> emitter;

	float hitAnimationTimer{ 1000 };

public:
	static inline Reference<WorldInstance> camera{};
};

