#ifndef AGUAMENTI_BULLETSCENE_H
#define AGUAMENTI_BULLETSCENE_H

#include "Particle.h"
#include "Precision.h"

class BulletScene
{
	static constexpr Aguamenti::Real BULLET_BURST_TIME = 0.3f;

public:
	void UpdateParticles(const Aguamenti::Real deltaTime);
	void DrawParticles(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection);
	void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext);

private:
	void AddParticle(ID3D11DeviceContext1& deviceContext, const Aguamenti::Real spawnPositionX, const Aguamenti::Real spawnPositionY);

private:
	Aguamenti::Real m_TimerBeforeAnotherBullet = 0.0f;
	bool m_HasFiredBullet = false;
	std::vector<Particle> m_Particles;
	std::vector< std::unique_ptr<DirectX::GeometricPrimitive>> m_ParticlesMeshes;
};

#endif