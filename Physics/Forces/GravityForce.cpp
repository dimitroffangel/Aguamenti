#include <pch.h>

#include <Physics/Forces/GravityForce.h>

void Aguamenti::GravityForce::ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle)
{
	particle.AddForce(m_Gravity);
}
