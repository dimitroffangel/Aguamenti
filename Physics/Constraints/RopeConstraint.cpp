#include <pch.h>
#include <Physics/Constraints/RopeConstraint.h>

#include <Component.h>
#include <Physics/Components/Particles/Particle.h>
#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

void Aguamenti::RopeConstraint::ApplyConstraintInContext(const Real deltaTime, ConstraintExecutionContext& constraintExecutionContext)
{
	if (constraintExecutionContext.m_ConstraintEntity.expired())
	{
		return;
	}
	if (constraintExecutionContext.m_AfflictedEntitiesByConstraint.size() != 1 || constraintExecutionContext.m_AfflictedEntitiesByConstraint[0].expired())
	{
		return;
	}

	PhysicsEntity& constraintEntity = *constraintExecutionContext.m_ConstraintEntity.lock();
	PhysicsEntity& entityTightToTheRope = *constraintExecutionContext.m_AfflictedEntitiesByConstraint[0].lock();
	
	ParticleComponent* constraintEntityParticleComponent = GetComponent<ParticleComponent>(constraintEntity);
	if (constraintEntityParticleComponent == nullptr)
	{
		return;
	}
	ParticleComponent* entityTightToTheRopeParticleComponent = GetComponent<ParticleComponent>(entityTightToTheRope);
	if (entityTightToTheRopeParticleComponent == nullptr)
	{
		return;
	}

	const Vector3 distanceVector = entityTightToTheRopeParticleComponent->m_CurrentPosition - constraintEntityParticleComponent->m_CurrentPosition;
	const Real squaredDistanceBetweenEntities = distanceVector.GetSquaredMagnitude();
	if (squaredDistanceBetweenEntities < m_MaxCableLength)
	{
		return;
	}

	m_CollisionInformation.m_LhsPhysicsEntity = constraintExecutionContext.m_ConstraintEntity;
	m_CollisionInformation.m_RhsPhysicsEntity = constraintExecutionContext.m_AfflictedEntitiesByConstraint[0];

	const Vector3 normal = distanceVector.GetNormalize();
	m_CollisionInformation.m_ContactNormal = normal;
	m_CollisionInformation.m_PenetrationLength = m_MaxCableLength;
	m_CollisionInformation.m_Restituion = m_MaxResitution;
}
