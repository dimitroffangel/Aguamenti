#ifndef AGUAMENTI_PARTICLE_H
#define AGUAMENTI_PARTICLE_H

#include "Core.h"
#include "Precision.h"

using namespace Aguamenti;

class Particle
{
private:
	Vector3 m_CurrentPosition;
	Vector3 m_Velocity;
	Vector3 m_Acceleration;
	Vector3 m_AccumulatedForce;

	Real m_Damping;
	Real m_InverseMass;

public:
	void Integrate(const Real deltaTime);
};

#endif