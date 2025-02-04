#pragma once

#include <Engine/Module/World/Mesh/StaticMeshInstance.h>
#include <Engine/Module/World/Particle/ParticleEmitterInstance.h>

class Billboard : public StaticMeshInstance {
public:
	Billboard(std::string name);

	virtual void fixed_update() override;

public:
	static inline Reference<WorldInstance> camera{};
};

class HitAnimation final {
public:
	HitAnimation(Vector3&& position);
	~HitAnimation() = default;

	__NON_COPYABLE_CLASS(HitAnimation)

public:
	void begin();
	void update();
	void transfer();
	void draw_billboard() const;
	void draw_particle() const;
	
public:
	bool is_end() const;

private:
	std::unique_ptr<Billboard> hitBillboard;
	std::unique_ptr<ParticleEmitterInstance> emitter;

	float hitAnimationTimer{ 1000 };

public:
	static inline Reference<WorldInstance> camera{};
	static inline Reference<WorldManager> worldManager{};
};

