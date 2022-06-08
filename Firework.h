#ifndef AGUAMENTI_FIREWORK_H
#define AGUAMENTI_FIREWORK_H

#include "Particle.h"

namespace Aguamenti
{
	class Firework : public Particle
	{
	public:
		void Update(const Real deltaTime)
		{
			m_Age -= deltaTime;
		}

	public:
		Real m_Age;
		int m_NumberOfHeirs;
	};
}

#endif

