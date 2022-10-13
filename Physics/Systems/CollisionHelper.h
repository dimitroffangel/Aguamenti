#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Systems/Entity/PhysicsEntityHelper.h>
#include <Physics/Core.h>
#include <Physics/Components/Particles/Particle.h>

namespace Aguamenti
{
	const Real RESTITUTION_DEFAULT = -0.75;

	void ResolveContact(const Real deltaTime, ParticleComponent* lhsParticleComponent, 
		ParticleComponent* rhsParticleComponent, const Vector3 contactNormal, const Real restitution = RESTITUTION_DEFAULT)
	{
		if (lhsParticleComponent == nullptr)
		{
			return;
		}

		Vector3 deltaVelocityBetweenParticleComponents = lhsParticleComponent->m_Velocity;
		if (rhsParticleComponent != nullptr)
		{
			deltaVelocityBetweenParticleComponents -= rhsParticleComponent->m_Velocity;
		}
		const Real seperatingVelocity = deltaVelocityBetweenParticleComponents * contactNormal;
		if (seperatingVelocity > 0)
		{
			return;
		}
		const Real newSeperatingVelocity = -seperatingVelocity * restitution;
		const Real deltaSeperatingVelocity = newSeperatingVelocity - seperatingVelocity;
		Real totalInverseMass = lhsParticleComponent->m_InverseMass;
		if (rhsParticleComponent != nullptr)
		{
			totalInverseMass += rhsParticleComponent->m_InverseMass;
		}
		// both objects are immovable
		if (totalInverseMass <= 0)
			return;

		const Real impulse = deltaSeperatingVelocity / totalInverseMass;
		const Vector3 directionPostContact = contactNormal * impulse;
		lhsParticleComponent->m_Velocity += lhsParticleComponent->m_Velocity + directionPostContact * lhsParticleComponent->m_InverseMass;
		if (rhsParticleComponent != nullptr)
		{
			rhsParticleComponent->m_Velocity += rhsParticleComponent->m_Velocity + directionPostContact * 
				rhsParticleComponent->m_InverseMass;
		}
	}
}


#endif