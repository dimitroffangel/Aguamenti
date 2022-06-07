#ifndef AGUAMENTI_PHYSICSSCENE_H
#define AGUAMENTI_PHYSICSSCENE_H

#include "Precision.h"
#include "Core.h"

#include "pch.h"

using namespace DirectX;

class PhysicsScene
{
public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) = 0;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void ApplyGravity() = 0;
	virtual void ApplyDragForce() = 0;

public:
	Aguamenti::Vector3 m_Gravity;
	Aguamenti::Real m_DragForceCoeficientK1;
	Aguamenti::Real m_DragForceCoeficientK2;
};

#endif