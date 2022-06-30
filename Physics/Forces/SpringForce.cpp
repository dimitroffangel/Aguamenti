#include <pch.h>

#include <Physics/Forces/SpringForce.h>

void Aguamenti::SpringForce::ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle)
{
	if (const std::shared_ptr<PhysicsEntity> otherSideEntity = m_OtherSideEntity.lock())
	{
		const ParticleComponent* const otherSideParticleComponent = GetComponent<ParticleComponent>(*otherSideEntity);
		assert(otherSideParticleComponent != nullptr);
		const Vector3 springVector = particle.m_CurrentPosition - otherSideParticleComponent->m_CurrentPosition;
		const Real springVectorMagnitude = (-m_SpringConstant) * (springVector.GetMagnitude() - m_DefaultSpringLength);
		const Vector3 springForce = springVector.GetNormalize() * springVectorMagnitude;

		particle.AddForce(springForce);
	}
}
