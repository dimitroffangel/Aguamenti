#include <pch.h>

#include <Physics/Forces/GravityForce.h>

void Aguamenti::GravityForce::ApplyForce(ParticleComponent& particle)
{
	particle.AddForce(m_Gravity);
}
