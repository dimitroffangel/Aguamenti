#ifndef AGUAMENTI_PHYSICSSCENE_H
#define AGUAMENTI_PHYSICSSCENE_H

#include <pch.h>
#include <vector>

#include <Physics/Precision.h>
#include <Physics/Core.h>
#include <Physics/Forces/Force.h>

using namespace DirectX;

class PhysicsScene
{
public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) = 0;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) = 0;
	virtual void HandleKeyboardEvent(const float deltaTime, const DirectX::Keyboard::State keyboardState, ID3D11DeviceContext1& deviceContext) {}

	void AddGravitationalForce(const Aguamenti::Vector3 gravity);
	void AddDragForce(const Aguamenti::Real k1, const Aguamenti::Real k2);

	virtual ~PhysicsScene() {}

protected:
	std::vector<std::unique_ptr<Aguamenti::Force>> m_Forces;
	std::vector<std::unique_ptr<Aguamenti::Force>> m_ParticleForces;
};

#endif