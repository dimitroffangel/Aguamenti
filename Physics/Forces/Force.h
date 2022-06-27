#ifndef AGUAMENTI_FORCE_H
#define AGUAMENTI_FORCE_H

#include <Physics/Components/Particles/Particle.h>
#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

namespace Aguamenti
{
	class Force
	{
	public:
		void ApplyForceInContext(PhysicsEntity& physicsEntity)
		{
			Aguamenti::ParticleComponent* particleComponent = GetComponent<Aguamenti::ParticleComponent>(physicsEntity);
			assert(particleComponent != nullptr);
			ApplyForce_Internal(*particleComponent);
		}

		virtual void ApplyForce_Internal(ParticleComponent& particle) = 0;
	};
}

#endif