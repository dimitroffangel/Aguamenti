#include <pch.h>

#include <Physics/Forces/GravityForce.h>

void Aguamenti::GravityForce::ApplyForce(Particle& particle)
{
	particle.AddForce(m_Gravity);
}
