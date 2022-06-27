#include <pch.h>

#include <Physics/Components/Particles/Particle.h>

void Aguamenti::ParticleComponent::AddForce(const Aguamenti::Vector3 forceToAdd)
{
	m_AccumulatedForce += forceToAdd;
}

void Aguamenti::ParticleComponent::Integrate(const Aguamenti::Real deltaTime)
{
	// 0.5*a*t^2 -> may cause cause floating problems
	m_CurrentPosition.AddScaledVector(m_Velocity, deltaTime);
	m_CurrentPosition.AddScaledVector(m_Acceleration, deltaTime * deltaTime * 0.5f);

	const Aguamenti::Vector3 updatedAcceleration = m_Acceleration + m_AccumulatedForce * m_InverseMass;
	m_Velocity.AddScaledVector(updatedAcceleration, deltaTime);
	m_Velocity *= pow(m_Damping, deltaTime);

	RemoveAllForcesApplied();
}

void Aguamenti::ParticleComponent::RemoveAllForcesApplied()
{
	m_AccumulatedForce = Aguamenti::Vector3(0, 0, 0);
}

void Aguamenti::ParticleComponent::Update(const Real deltaTime)
{
	Integrate(deltaTime);
}
