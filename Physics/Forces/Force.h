#ifndef AGUAMENTI_FORCE_H
#define AGUAMENTI_FORCE_H

#include <Physics/Particles/Particle.h>

namespace Aguamenti
{
	class Force
	{
	public:
		virtual void ApplyForce(Particle& particle) = 0;
	};
}

#endif