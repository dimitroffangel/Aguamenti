#include "pch.h"
#include "ImmovableRodConstraint.h"

#include <Physics/Components/Particles/Particle.h>
#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

void Aguamenti::ImmovableRodConstraint::ApplyConstraintInContext(const Real deltaTime, ConstraintExecutionContext& constraintExecutionContext)
{
	if (constraintExecutionContext.m_AfflictedEntitiesByConstraint.size() != EXPECTED_NUMBER_OF_ENTITIES_TO_BE_AFFLICTED)
	{
		return;
	}
	if (constraintExecutionContext.m_AfflictedEntitiesByConstraint[0].expired() || constraintExecutionContext.m_AfflictedEntitiesByConstraint[1].expired())
	{
		return;
	}

	PhysicsEntity& lhsRodSide = *constraintExecutionContext.m_AfflictedEntitiesByConstraint[0].lock();
	PhysicsEntity& rhsRodSide = *constraintExecutionContext.m_AfflictedEntitiesByConstraint[1].lock();
	ParticleComponent* lhsParticleComponent = GetComponent<ParticleComponent>(lhsRodSide);
	if (lhsParticleComponent == nullptr)
	{
		return;
	}
	ParticleComponent* rhsParticleComponent = GetComponent<ParticleComponent>(rhsRodSide);
	if (rhsParticleComponent == nullptr)
	{
		return;
	}
	const Vector3 distanceVector = rhsParticleComponent->m_CurrentPosition - lhsParticleComponent->m_CurrentPosition;
	const Real currentLength = distanceVector.GetMagnitude();
	if (currentLength == m_Length * m_Length)
	{
		return;
	}

	CollisionInformation collisionInformation;
	collisionInformation.m_LhsPhysicsEntity = constraintExecutionContext.m_AfflictedEntitiesByConstraint[0];
	collisionInformation.m_RhsPhysicsEntity = constraintExecutionContext.m_AfflictedEntitiesByConstraint[1];
	collisionInformation.m_Restituion = 0;
	const Vector3 normalizedDistanceVector = distanceVector.GetNormalize();
	if (currentLength > m_Length)
	{
		collisionInformation.m_ContactNormal = normalizedDistanceVector;
		collisionInformation.m_PenetrationLength = currentLength - m_Length;
	}
	else
	{
		collisionInformation.m_ContactNormal = normalizedDistanceVector * (-1);
		collisionInformation.m_PenetrationLength = m_Length - currentLength;
	}
}
