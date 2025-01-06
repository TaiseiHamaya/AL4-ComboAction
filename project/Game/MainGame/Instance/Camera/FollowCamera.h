#pragma once

#include <Engine/Module/World/Camera/Camera3D.h>

class FollowCamera final : public Camera3D {
public:
	void initialize() override;
	void update();
	void update_matrix();

	void input();

public:
	void set_offset(const Vector3& offset_);
	const Vector3& get_offset() const;

	void set_target(const WorldInstance* target_);

#ifdef _DEBUG
public:
	void debug_gui() override;
#endif // _DEBUG

private:
	Vector3 offset;

	bool isPressX;
	Vector2 inputStickR;

	const WorldInstance* target;
	WorldInstance lookAtInstance;
	Quaternion destingRotation;
};

