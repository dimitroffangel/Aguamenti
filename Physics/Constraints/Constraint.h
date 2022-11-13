#ifndef AGUAMENTI_CONSTRAINT_H
#define AGUAMENTI_CONSTRAINT_H

#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Precision.h>
#include <Physics/Entity/CollisionInformation.h>

namespace Aguamenti
{
	struct ConstraintExecutionContext
	{
		std::weak_ptr<PhysicsEntity> m_ConstraintEntity;
		std::vector<std::weak_ptr<PhysicsEntity>> m_AfflictedEntityByConstraint;
	};

	class Constraint
	{
	public:
		virtual ~Constraint()
		{

		}
		
		CollisionInformation m_CollisionInformation;

		virtual void ApplyConstraintInContext(const Real deltaTime, ConstraintExecutionContext& constraintExecutionContext) = 0;
	};
}

#endif