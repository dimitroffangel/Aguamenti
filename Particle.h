#ifndef AGUAMENTI_PARTICLE_H
#define AGUAMENTI_PARTICLE_H

#include "Core.h"
#include "Precision.h"

class Particle
{
public:
	Particle()
	{

	}

	Particle(const Aguamenti::Vector3& initialPosition, const Aguamenti::Vector3& velocity, const Aguamenti::Vector3& acceleration, const Aguamenti::Real damping, const Aguamenti::Real inverseMass)
		: m_CurrentPosition(initialPosition), m_Velocity(velocity), m_Acceleration(acceleration), m_Damping(damping), m_InverseMass(inverseMass)

	{

	}

public:
	Aguamenti::Vector3 m_CurrentPosition;
	Aguamenti::Vector3 m_Velocity;
	Aguamenti::Vector3 m_Acceleration;
	Aguamenti::Vector3 m_AccumulatedForce;

	Aguamenti::Real m_Damping;
	Aguamenti::Real m_InverseMass;

public:
	void AddForce(const Aguamenti::Vector3 forceToAdd);
	void Integrate(const Aguamenti::Real deltaTime);

private:
	void RemoveAllForcesApplied();
};

#endif