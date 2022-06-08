#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Forces/Force.h>

namespace Aguamenti
{
	template<typename PhysicsObject>
	void ApplyForce(const std::vector<std::unique_ptr<Force>>& forcesToApply, std::vector<PhysicsObject>& physicsObjects)
	{
		for (PhysicsObject physicsObject : physicsObjects)
		{
			for (const auto& force : forcesToApply)
			{
				force->ApplyForce(physicsObject);
			}
		}
	}
};

#endif