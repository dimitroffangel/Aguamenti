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
		const Vector3 contactNormal)
	{
		if (penetrationLength <= 0)
		{
			return;
		}
		if (lhsParticleComponent == nullptr)
		{
			assert(false && "Aguamenti::ResolveInterpenetration lhsParticleComponent does not exist");
			return;
		}

		Real totalInverseMass = lhsParticleComponent->m_InverseMass;
		if (rhsParticleComponent != nullptr)
		{
			totalInverseMass += rhsParticleComponent->m_InverseMass;
		}
		const Vector3 moveBasedOnTotalInverseMass = contactNormal * (-penetrationLength * totalInverseMass);
		lhsParticleComponent->m_CurrentPosition += lhsParticleComponent->m_CurrentPosition + moveBasedOnTotalInverseMass *
			lhsParticleComponent->m_InverseMass;
		if (rhsParticleComponent != nullptr)
		{
			rhsParticleComponent->m_CurrentPosition += rhsParticleComponent->m_CurrentPosition + moveBasedOnTotalInverseMass *
				rhsParticleComponent->m_InverseMass;
		}
	}
}


#endif