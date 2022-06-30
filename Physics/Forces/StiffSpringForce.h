#ifndef AGUAMENTI_STIFFSPRINGFORCE_H
#define AGUAMENTI_STIFFSPRINGFORCE_H

#include <Physics/Forces/Force.h>

namespace Aguamenti
{
	class StiffSpringForce : public Force
	{
	public:
		StiffSpringForce(const std::shared_ptr<PhysicsEntity>& otherSideEntity, const Real springConstant, const Real damping)
			: m_OtherSideEntity(otherSideEntity), m_SpringConstant(springConstant), m_Damping(m_Damping)
		{

		}

	private:
		// Inherited via Force
		virtual void ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle) override;

	public:
		std::weak_ptr<PhysicsEntity> m_OtherSideEntity;
		Real m_SpringConstant;
		Real m_Damping;
	};
}

#endif

