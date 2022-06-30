#include <pch.h>

#include <Physics/Forces/StiffSpringForce.h>

void Aguamenti::StiffSpringForce::ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle)
{
	if (const std::shared_ptr<PhysicsEntity> otherSideEntity = m_OtherSideEntity.lock())
	{
		const ParticleComponent* const otherSideParticleComponent = GetComponent<ParticleComponent>(*otherSideEntity);
		assert(otherSideParticleComponent != nullptr);

		const Vector3 differenceBetweenSpringsEnd = particle.m_CurrentPosition - otherSideParticleComponent->m_CurrentPosition;
		const Real gamma = REAL_SQRT(4 * m_SpringConstant - m_Damping * m_Damping) * 0.5f;
		if (gamma == 0)
		{
			return;
		}
		const Vector3 c = differenceBetweenSpringsEnd * (m_Damping / (2 * gamma))  + particle.m_Velocity * (1 / gamma);
		const Vector3 targetPosition = (differenceBetweenSpringsEnd * cosf(gamma * deltaTime) + c * sinf(gamma * deltaTime))
			* expf(-0.5f * deltaTime * m_Damping);
		const Vector3 acceleration = differenceBetweenSpringsEnd / (particle.m_Acceleration * particle.m_Acceleration) - 
			particle.m_Velocity * deltaTime;

		particle.AddForce(acceleration *  (1.0f / particle.m_InverseMass));
	}

}
