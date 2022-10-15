#include <pch.h>
#include <Physics/Systems/CollisionHelper.h>

bool Aguamenti::CalculateSeparatingVelocity(CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_LhsParticleComponent.expired())
	{
		assert(false && "Aguamenti::CalculateSeparatingVelocity collisionInformation.m_LhsParticleComponent(the particle's component from which point the collision is happnenning) does not exist");
		return false;
	}

	std::shared_ptr<ParticleComponent> lhsParticleComponent = collisionInformation.m_LhsParticleComponent.lock();
	Vector3 deltaVelocityBetweenParticleComponents = lhsParticleComponent->m_Velocity;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		deltaVelocityBetweenParticleComponents -= rhsParticleComponent->m_Velocity;
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
	if (collisionInformation.m_LhsParticleComponent.expired())
	{
		assert(false && "Aguamenti::ResolveContact collisionInformation.m_LhsParticleComponent(the particle's component from which point the collision is happnenning) does not exist");
		return;
	}

	std::shared_ptr<ParticleComponent> lhsParticleComponent = collisionInformation.m_LhsParticleComponent.lock();
	Vector3 accelerationOfSeparatingVelocity = lhsParticleComponent->m_Acceleration;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		accelerationOfSeparatingVelocity -= rhsParticleComponent->m_Acceleration;
	}
	const Real acceleratedSeparatingVelocity = accelerationOfSeparatingVelocity * collisionInformation.m_ContactNormal * deltaTime;
	Real newSeparatingVelocity = -separatingVelocity * collisionInformation.m_Restituion;
	if (acceleratedSeparatingVelocity < 0)
	{
		newSeparatingVelocity += collisionInformation.m_Restituion * acceleratedSeparatingVelocity;
		if (newSeparatingVelocity < 0)
		{
			newSeparatingVelocity = 0;
		}
	}

	Real totalInverseMass = lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		totalInverseMass += rhsParticleComponent->m_InverseMass;
	}
	// both objects are immovable
	if (totalInverseMass <= 0)
		return;

	const Real deltaSeparatingVelocity = newSeparatingVelocity - separatingVelocity;
	const Real impulse = deltaSeparatingVelocity / totalInverseMass;
	const Vector3 directionAfterContact = collisionInformation.m_ContactNormal * impulse;
	lhsParticleComponent->m_Velocity += directionAfterContact * lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		rhsParticleComponent->m_Velocity += directionAfterContact * (-rhsParticleComponent->m_InverseMass);
	}
}

void Aguamenti::ResolveInterpenetration(const Real deltaTime, const CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_PenetrationLength <= 0)
	{
		return;
	}
	if (collisionInformation.m_LhsParticleComponent.expired())
	{
		assert(false && "Aguamenti::ResolveInterpenetration collisionInformation.m_LhsParticleComponent(the particle's component from which point the collision is happnenning) does not exist");
		return;
	}
	std::shared_ptr<ParticleComponent> lhsParticleComponent = collisionInformation.m_LhsParticleComponent.lock();
	Real totalInverseMass = lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		totalInverseMass += rhsParticleComponent->m_InverseMass;
	}
	const Vector3 moveBasedOnTotalInverseMass = collisionInformation.m_ContactNormal * (collisionInformation.m_PenetrationLength * totalInverseMass);
	lhsParticleComponent->m_CurrentPosition += moveBasedOnTotalInverseMass * lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<ParticleComponent> rhsParticleComponent = collisionInformation.m_RhsParticleComponent.lock())
	{
		rhsParticleComponent->m_CurrentPosition -= moveBasedOnTotalInverseMass * (rhsParticleComponent->m_InverseMass);
	}
}