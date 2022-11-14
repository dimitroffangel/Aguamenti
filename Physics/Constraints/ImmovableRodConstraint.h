#ifndef AGUAMENTI_IMMOVABLERODCONSTRAINT_H
#define AGUAMENTI_IMMOVABLERODCONSTRAINT_H

#include <Physics/Constraints/Constraint.h>


namespace Aguamenti
{
	class ImmovableRodConstraint : public Constraint
	{
		const size_t EXPECTED_NUMBER_OF_ENTITIES_TO_BE_AFFLICTED = 2;

	public:
		virtual void ApplyConstraintInContext(const Real deltaTime, ConstraintExecutionContext& constraintExecutionContext) override;

		Real m_Length;
	};
}

#endif