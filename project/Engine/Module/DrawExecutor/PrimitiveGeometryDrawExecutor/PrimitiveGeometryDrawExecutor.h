#pragma once

#ifdef _DEBUG

#include "../BaseDrawExecutor.h"

#include "Engine/Rendering/DirectX/DirectXResourceObject/StructuredBuffer/StructuredBuffer.h"
#include "Engine/Resources/PrimitiveGeometry/PrimitiveGeometryResource.h"

#include <Library/Math/Matrix4x4.h>

class PrimitiveGeometryDrawExecutor final : BaseDrawExecutor<PrimitiveGeometryResource> {
public:
	PrimitiveGeometryDrawExecutor() = default;
	virtual ~PrimitiveGeometryDrawExecutor() = default;

	__DRAW_EXECUTOR_CLASS(PrimitiveGeometryDrawExecutor)

public:
	void reinitialize(const std::string& primitiveGeometryName, uint32_t maxInstance) override;
	void draw_command(uint32_t InstanceCount) const override;
	void write_to_buffer(uint32_t index, const Matrix4x4& worldMatrix);

private:
	StructuredBuffer<Matrix4x4> matrices;
};

#endif // _DEBUG
