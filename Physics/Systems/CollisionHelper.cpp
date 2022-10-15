#include <pch.h>
#include <Physics/Systems/CollisionHelper.h>

bool Aguamenti::CalculateSeparatingVelocity(CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_LhsParticleComponent == nullptr)
	{
		assert(false && "Aguamenti::CalculateSeparatingVelocity collisionInformation.m_LhsParticleComponent(the particle's component from which point the collision is happnenning) does not exist");
		return false;
	}

	Vector3 deltaVelocityBetweenParticleComponents = collisionInformation.m_LhsParticleComponent->m_Velocity;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		deltaVelocityBetweenParticleComponents -= collisionInformation.m_RhsParticleComponent->m_Velocity;
	}

	collisionInformation.m_SeparationVelocity = deltaVelocityBetweenParticleComponents * collisionInformation.m_ContactNormal;
	return true;
}

void Aguamenti::ResolveContact(const Real deltaTime, const CollisionInformation& collisionInformation)
{
	const Real separatingVelocity = collisionInformation.m_SeparationVelocity;
	if (separatingVelocity > 0)
	{
		return;
	}
	Real newSeparatingVelocity = -separatingVelocity * collisionInformation.m_Restituion;
	Vector3 accelerationOfSeparatingVelocity = collisionInformation.m_LhsParticleComponent->m_Acceleration;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		accelerationOfSeparatingVelocity -= collisionInformation.m_RhsParticleComponent->m_Acceleration;
	}
	const Real acceleratedSeparatingVelocity = accelerationOfSeparatingVelocity * collisionInformation.m_ContactNormal * deltaTime;
	if (acceleratedSeparatingVelocity < 0)
	{
		newSeparatingVelocity += collisionInformation.m_Restituion * acceleratedSeparatingVelocity;

		if (newSeparatingVelocity < 0)
		{
			newSeparatingVelocity = 0;
		}
	}

	const Real deltaSeparatingVelocity = newSeparatingVelocity - separatingVelocity;
	Real totalInverseMass = collisionInformation.m_LhsParticleComponent->m_InverseMass;
	if (collisionInformation.m_RhsParticleComponent != nullptr)
	{
		totalInverseMass += collisionInformation.m_RhsParticleComponent->m_InverseMass;
	}
	// both objects are immovable
	if (totalInverseMass <= 0)
		return;

	const Real impulse = deltaSeparatingVelocity / totalInverseMass;
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
		assert(false && "Aguamenti::ResolveInterpenetration collisionInformation.m_LhsParticleComponent(the particle's component from which point the collision is happnenning) does not exist");
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