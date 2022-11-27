#ifndef AGUAMENTI_BRIDGESCENE_H
#define AGUAMENTI_BRIDGESCENE_H

#include <PhysicScenes/PhysicsScene.h>
#include <vector>

#include <Physics/Precision.h>
#include <Physics/Core.h>
#include <Physics/Forces/Force.h>

using namespace DirectX;

class BridgeScene : public PhysicsScene
{
	static constexpr Aguamenti::Real BULLET_BURST_TIME = 0.3f;

public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) override {};
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) override;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) override;
	virtual void HandleKeyboardEvent(const float deltaTime, const DirectX::Keyboard::State keyboardState, ID3D11DeviceContext1& deviceContext) override;

private:
	bool m_HasCreatedPlayerParticle = false;
	Aguamenti::Real m_TimerBeforeAnotherBullet = 0.0f;
	std::vector<std::shared_ptr<Aguamenti::PhysicsEntity>> m_PlayerParticles;
};

#endif

