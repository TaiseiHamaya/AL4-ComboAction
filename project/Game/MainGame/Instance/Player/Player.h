#pragma once

#include <Engine/Module/World/AnimatedMesh/AnimatedMeshInstance.h>

class Player final : public AnimatedMeshInstance {
public:
	Player();
	~Player() = default;
};
