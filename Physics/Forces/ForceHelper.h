#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Forces/Force.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>
#include <Physics/Components/RelativeForceComponent.h>

namespace Aguamenti
{
	template<typename PhysicsObject>
	void ApplyForce(const std::vector<std::unique_ptr<Force>>& forcesToApply, std::vector<std::shared_ptr<PhysicsObject>>& physicsObjects)
	{
		for (const std::shared_ptr<PhysicsObject>& physicsObject : physicsObjects)
		{
			for (const auto& force : forcesToApply)
			{
				force->ApplyForceInContext(*physicsObject);
			}
		}
	}

	void AddRelativeGravitationalForce(RelativeForceComponent& relativeComponent);
};

#endif