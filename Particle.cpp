#include "pch.h"
#include "Particle.h"

void Particle::AddForce(const Aguamenti::Vector3 forceToAdd)
{
	m_AccumulatedForce += forceToAdd;
}

void Particle::Integrate(const Aguamenti::Real deltaTime)
{
	// 0.5*a*t^2 -> may cause cause floating problems
	m_CurrentPosition.AddScaledVector(m_Velocity, deltaTime);
	m_CurrentPosition.AddScaledVector(m_Acceleration, deltaTime * deltaTime * 0.5f);

	const Aguamenti::Vector3 updatedAcceleration = m_Acceleration + m_AccumulatedForce * m_InverseMass;
	m_Velocity.AddScaledVector(updatedAcceleration, deltaTime);
	m_Velocity *= pow(m_Damping, deltaTime);

	RemoveAllForcesApplied();
}

void Particle::RemoveAllForcesApplied()
{
	m_AccumulatedForce = Aguamenti::Vector3(0, 0, 0);
}
