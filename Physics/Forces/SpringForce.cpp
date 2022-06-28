#include <pch.h>

#include <Physics/Forces/SpringForce.h>

void Aguamenti::SpringForce::ApplyForce_Internal(ParticleComponent& particle)
{
	const Vector3 particlePosition = particle.m_CurrentPosition;
	const Real particleMagnitude = (-m_SpringConstant) * (particlePosition.GetMagnitude() - m_DefaultSpringLength);
	const Vector3 springForce = particle.m_CurrentPosition.GetNormalize() * particleMagnitude;

	particle.AddForce(springForce);
}
