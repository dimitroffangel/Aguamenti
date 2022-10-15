#include <pch.h>
#include <Physics/Systems/CollisionHelper.h>

bool Aguamenti::CalculateSeperatingVelocity(CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_LhsParticleComponent == nullptr)
	{
		assert(false && "Aguamenti::CalculateSeperatingVelocity collisionInformation.m_LhsParticleComponent  does not exist");
		return false;
	}

	Vector3 deltaVelocityBetweenParticleComponents = collisionInformation.m_LhsParticleComponent->m_Velocity;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		deltaVelocityBetweenParticleComponents -= collisionInformation.m_RhsParticleComponent->m_Velocity;
	}

	collisionInformation.m_SeperationVelocity = deltaVelocityBetweenParticleComponents * collisionInformation.m_ContactNormal;
	return true;
}

void Aguamenti::ResolveContact(const Real deltaTime, const CollisionInformation& collisionInformation)
{
	const Real separatingVelocity = collisionInformation.m_SeperationVelocity;
	if (separatingVelocity > 0)
	{
		return;
	}
	Real newSeperatingVelocity = -separatingVelocity * collisionInformation.m_Restituion;
	Vector3 accelerationOfSeperatingVelocity = collisionInformation.m_LhsParticleComponent->m_Acceleration;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		accelerationOfSeperatingVelocity -= collisionInformation.m_RhsParticleComponent->m_Acceleration;
	}
	const Real acceleratedSeperatingVelocity = accelerationOfSeperatingVelocity * collisionInformation.m_ContactNormal * deltaTime;
	if (acceleratedSeperatingVelocity < 0)
	{
		newSeperatingVelocity += collisionInformation.m_Restituion * acceleratedSeperatingVelocity;

		if (newSeperatingVelocity < 0)
		{
			newSeperatingVelocity = 0;
		}
	}

	const Real deltaSeperatingVelocity = newSeperatingVelocity - separatingVelocity;
	Real totalInverseMass = collisionInformation.m_LhsParticleComponent->m_InverseMass;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		totalInverseMass += collisionInformation.m_RhsParticleComponent->m_InverseMass;
	}
	// both objects are immovable
	if (totalInverseMass <= 0)
		return;

	const Real impulse = deltaSeperatingVelocity / totalInverseMass;
	const Vector3 directionPostContact = collisionInformation.m_ContactNormal * impulse;
	collisionInformation.m_LhsParticleComponent->m_Velocity += 
		collisionInformation.m_LhsParticleComponent->m_Velocity + 
		directionPostContact * collisionInformation.m_LhsParticleComponent->m_InverseMass;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		collisionInformation.m_RhsParticleComponent->m_Velocity += 
			collisionInformation.m_RhsParticleComponent->m_Velocity + directionPostContact *
			collisionInformation.m_RhsParticleComponent->m_InverseMass;
	}
}

void Aguamenti::ResolveInterpenetration(const Real deltaTime, const CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_PenetrationLength <= 0)
	{
		return;
	}
	if (collisionInformation.m_LhsParticleComponent == nullptr)
	{
		assert(false && "Aguamenti::ResolveInterpenetration collisionInformation.m_LhsParticleComponent does not exist");
		return;
	}

	Real totalInverseMass = collisionInformation.m_LhsParticleComponent->m_InverseMass;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		totalInverseMass += collisionInformation.m_RhsParticleComponent->m_InverseMass;
	}
	const Vector3 moveBasedOnTotalInverseMass = collisionInformation.m_ContactNormal * (-collisionInformation.m_PenetrationLength* totalInverseMass);
	collisionInformation.m_LhsParticleComponent->m_CurrentPosition += 
		collisionInformation.m_LhsParticleComponent->m_CurrentPosition + moveBasedOnTotalInverseMass *
		collisionInformation.m_LhsParticleComponent->m_InverseMass;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		collisionInformation.m_RhsParticleComponent->m_CurrentPosition += 
			collisionInformation.m_RhsParticleComponent->m_CurrentPosition + moveBasedOnTotalInverseMass *
			collisionInformation.m_RhsParticleComponent->m_InverseMass;
	}
}