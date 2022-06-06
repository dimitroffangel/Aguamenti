#ifndef AGUAMENTI_PHYSICSSCENE_H
#define AGUAMENTI_PHYSICSSCENE_H

#include "Precision.h"
#include "pch.h"

using namespace DirectX;

class PhysicsScene
{
public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) = 0;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) = 0;
};

#endif