#include <pch.h>
#include <Physics/Systems/CollisionHelper.h>

void Aguamenti::ResolveContact(const Real deltaTime, ParticleComponent* lhsParticleComponent, ParticleComponent* rhsParticleComponent, const Vector3 contactNormal, const Real restitution)
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

void Aguamenti::ResolveInterpenetration(const Real deltaTime, ParticleComponent* lhsParticleComponent, ParticleComponent* rhsParticleComponent, const Real penetrationLength, const Vector3 contactNormal)
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