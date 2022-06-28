#ifndef AGUAMENTI_SPRINGFORCE_H
#define AGUAMENTI_SPRINGFORCE_H

#include <Physics/Forces/Force.h>
#include <Physics/Core.h>
#include <Physics/Entity/PhysicsEntity.h>

namespace Aguamenti
{
	class SpringForce : public Force
	{
	public:
		SpringForce(const std::shared_ptr<PhysicsEntity>& otherSideEntity, const Real springConstant, const Real defaultSpringLength)
			: m_OtherSideEntity(otherSideEntity), m_SpringConstant(springConstant), m_DefaultSpringLength(defaultSpringLength)
		{

		}

	private:
		// Inherited via Force
		virtual void ApplyForce_Internal(ParticleComponent& particle) override;

	public:
		std::weak_ptr<PhysicsEntity> m_OtherSideEntity;
		Real m_SpringConstant;
		Real m_DefaultSpringLength;
	};
}

#endif

