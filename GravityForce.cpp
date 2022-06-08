#include "pch.h"
#include "GravityForce.h"

void Aguamenti::GravityForce::ApplyForce(Particle& particle)
{
	particle.AddForce(m_Gravity);
}
