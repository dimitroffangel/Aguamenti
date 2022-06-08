#ifndef AGUAMENTI_PHYSICSSCENE_H
#define AGUAMENTI_PHYSICSSCENE_H

#include <pch.h>

#include <Physics/Precision.h>
#include <Physics/Core.h>
#include <Physics/Forces/Force.h>

#include <vector>

using namespace DirectX;

class PhysicsScene
{
public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) = 0;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) = 0;

	void AddGravitationalForce(const Aguamenti::Vector3 gravity);
	void AddDragForce(const Aguamenti::Real k1, const Aguamenti::Real k2);

protected:
	std::vector<std::unique_ptr<Aguamenti::Force>> m_Forces;
};

#endif