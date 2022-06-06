#ifndef AGUAMENTI_FIREWORK_H
#define AGUAMENTI_FIREWORK_H

#include "Particle.h"

class Firework : public Particle
{
public:
	void Update(const Aguamenti::Real deltaTime)
	{
		m_Age -= deltaTime;
	}

public:
	Aguamenti::Real m_Age;
	int m_NumberOfHeirs;
};

#endif

