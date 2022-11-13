#include <pch.h>
#include <Physics/Systems/CollisionHelper.h>

bool Aguamenti::CalculateSeparatingVelocity(CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_LhsPhysicsEntity.expired())
	{
		assert(false && "Aguamenti::CalculateSeparatingVelocity collisionInformation.m_LhsPhysicsEntity (the physics entity from which point the collision is happnenning) does not exist");
		return false;
	}

	PhysicsEntity& lhsPhysicsEntity = *collisionInformation.m_LhsPhysicsEntity.lock();
	ParticleComponent* lhsParticleComponent = GetComponent<ParticleComponent>(lhsPhysicsEntity);
	if (lhsParticleComponent == nullptr)
	{
		return false;
	}

	Vector3 deltaVelocityBetweenParticleComponents = lhsParticleComponent->m_Velocity;
	if (std::shared_ptr<PhysicsEntity> rhsPhysicsEntity = collisionInformation.m_RhsPhysicsEntity.lock())
	{
		ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(*rhsPhysicsEntity);
		if (rhsParticleComponent == nullptr)
		{
			return false;
		}

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
	if (collisionInformation.m_LhsPhysicsEntity.expired())
	{
		assert(false && "Aguamenti::ResolveContact collisionInformation.m_LhsPhysicsEntity (the physics entity from which point the collision is happnenning) does not exist");
		return;
	}

	PhysicsEntity& lhsPhysicsEntity = *collisionInformation.m_LhsPhysicsEntity.lock();
	ParticleComponent* lhsParticleComponent = GetComponent<ParticleComponent>(lhsPhysicsEntity);
	if (lhsParticleComponent == nullptr)
	{
		return;
	}
	Vector3 accelerationOfSeparatingVelocity = lhsParticleComponent->m_Acceleration;
	Real totalInverseMass = lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<PhysicsEntity> rhsPhysicsEntity = collisionInformation.m_RhsPhysicsEntity.lock())
	{
		ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(*rhsPhysicsEntity);
		if (rhsParticleComponent == nullptr)
		{
			return;
		}

		accelerationOfSeparatingVelocity -= rhsParticleComponent->m_Acceleration;
		totalInverseMass += rhsParticleComponent->m_InverseMass;

	}
	// both objects are immovable
	if (totalInverseMass <= 0)
	{
		return;
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

	const Real deltaSeparatingVelocity = newSeparatingVelocity - separatingVelocity;
	const Real impulse = deltaSeparatingVelocity / totalInverseMass;
	const Vector3 directionAfterContact = collisionInformation.m_ContactNormal * impulse;
	lhsParticleComponent->m_Velocity += directionAfterContact * lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<PhysicsEntity> rhsPhysicsEntity = collisionInformation.m_RhsPhysicsEntity.lock())
	{
		ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(*rhsPhysicsEntity);
		if (rhsParticleComponent == nullptr)
		{
			return;
		}

		rhsParticleComponent->m_Velocity += directionAfterContact * (-rhsParticleComponent->m_InverseMass);
	}
}

void Aguamenti::ResolveInterpenetration(const Real deltaTime, const CollisionInformation& collisionInformation)
{
	if (collisionInformation.m_PenetrationLength <= 0)
	{
		return;
	}
	if (collisionInformation.m_LhsPhysicsEntity.expired())
	{
		assert(false && "Aguamenti::ResolveInterpenetration collisionInformation.m_LhsPhysicsEntity (the physics entity from which point the collision is happnenning) does not exist");
		return;
	}

	PhysicsEntity& lhsPhysicsEntity = *collisionInformation.m_LhsPhysicsEntity.lock();
	ParticleComponent* lhsParticleComponent = GetComponent<ParticleComponent>(lhsPhysicsEntity);
	if (lhsParticleComponent == nullptr)
	{
		return;
	}
	Real totalInverseMass = lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<PhysicsEntity> rhsPhysicsEntity = collisionInformation.m_RhsPhysicsEntity.lock())
	{
		ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(*rhsPhysicsEntity);
		if (rhsParticleComponent == nullptr)
		{
			return;
		}

		totalInverseMass += rhsParticleComponent->m_InverseMass;
	}
	const Vector3 moveBasedOnTotalInverseMass = collisionInformation.m_ContactNormal * (collisionInformation.m_PenetrationLength * totalInverseMass);
	lhsParticleComponent->m_CurrentPosition += moveBasedOnTotalInverseMass * lhsParticleComponent->m_InverseMass;
	if (std::shared_ptr<PhysicsEntity> rhsPhysicsEntity = collisionInformation.m_RhsPhysicsEntity.lock())
	{
		ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(*rhsPhysicsEntity);
		if (rhsParticleComponent == nullptr)
		{
			return;
		}

		rhsParticleComponent->m_CurrentPosition -= moveBasedOnTotalInverseMass * (rhsParticleComponent->m_InverseMass);
	}
}