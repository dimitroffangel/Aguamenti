#ifndef AGUAMENTI_FORCE_H
#define AGUAMENTI_FORCE_H

#include <Physics/Components/Particles/Particle.h>

namespace Aguamenti
{
	class Force
	{
	public:
		virtual void ApplyForce(ParticleComponent& particle) = 0;
	};
}

#endif