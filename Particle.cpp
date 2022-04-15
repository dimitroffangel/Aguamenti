#include "Particle.h"

void Particle::Integrate(const Real deltaTime)
{
	m_CurrentPosition.AddScaledVector(m_Velocity, deltaTime);

	const Vector3 updatedAcceleration = m_Acceleration * deltaTime;

	m_Velocity *= pow(m_Damping, deltaTime);

	m_Velocity.AddScaledVector(updatedAcceleration, deltaTime);
}
