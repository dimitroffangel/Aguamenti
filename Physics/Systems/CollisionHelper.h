#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Systems/Entity/PhysicsEntityHelper.h>
#include <Physics/Core.h>
#include <Physics/Components/Particles/Particle.h>

namespace Aguamenti
{
	const Real RESTITUTION_DEFAULT = -0.75;

	void ResolveContact(const Real deltaTime, ParticleComponent* lhsParticleComponent,
		ParticleComponent* rhsParticleComponent, const Vector3 contactNormal, const Real restitution = RESTITUTION_DEFAULT);
	void ResolveInterpenetration(const Real deltaTime,
		ParticleComponent* lhsParticleComponent, ParticleComponent* rhsParticleComponent, const Real penetrationLength,
		const Vector3 contactNormal);
}


#endif