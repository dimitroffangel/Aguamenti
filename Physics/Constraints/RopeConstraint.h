#ifndef AGUAMENTI_ROPECONSTRAINT_H
#define AGUAMENTI_ROPECONSTRAINT_H

#include <Physics/Constraints/Constraint.h>

namespace Aguamenti
{
	class RopeConstraint : public Constraint
	{
	public:
		Real m_MaxCableLength;
		Real m_MaxResitution;

		virtual void ApplyConstraintInContext(const Real deltaTime, ConstraintExecutionContext& constraintExecutionContext) override;
	};
}

#endif