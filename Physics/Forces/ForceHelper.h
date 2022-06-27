#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Forces/Force.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

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
};

#endif