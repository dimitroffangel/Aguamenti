#ifndef AGUAMENTI_BULLETSCENE_H
#define AGUAMENTI_BULLETSCENE_H

#include <Physics/Components/Particles/Particle.h>
#include <PhysicScenes/PhysicsScene.h>
#include <Physics/Entity/PhysicsEntity.h>

class BulletScene : public PhysicsScene
{
	static constexpr Aguamenti::Real BULLET_BURST_TIME = 0.3f;

public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) override;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) override;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) override;

private:
	void AddParticle(ID3D11DeviceContext1& deviceContext, const Aguamenti::Real spawnPositionX, const Aguamenti::Real spawnPositionY);

private:
	Aguamenti::Real m_TimerBeforeAnotherBullet = 0.0f;
	bool m_HasFiredBullet = false;
	std::vector<std::shared_ptr<Aguamenti::PhysicsEntity>> m_Particles;
};

#endif