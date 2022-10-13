#ifndef AGUAMENTI_RELATIVEFORCECOMPONENT_H
#define AGUAMENTI_RELATIVEFORCECOMPONENT_H

#include <Component.h>
#include <Physics/Precision.h>
#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Forces/Force.h>

namespace Aguamenti
{
	class RelativeForceComponent : public Component
	{
	public:
		// Inherited via Component
		virtual void Update(const Real deltaTime) override;

		virtual void ApplyForces(PhysicsEntity& physicsEntity)
		{
			for (const std::shared_ptr<Force>& force : m_Forces)
			{
				force->ApplyForceInContext(physicsEntity);
			}
		}

		std::vector<std::shared_ptr<Force>> m_Forces;
	};
}

#endif
