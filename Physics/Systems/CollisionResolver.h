#ifndef AGUAMENTI_COLLISIONRESOLVER_H
#define AGUAMENTI_COLLISIONRESOLVER_H

#include <Physics/Entity/PhysicsEntity.h>
#include <Physics/Entity/CollisionInformation.h>

namespace Aguamenti
{
	class CollisionResolver
	{
	private:
		size_t m_MaxNumberOfIterations = 64;
		size_t m_CurrentNumberOfIterations = 0;

	public:
		void GatherCollisions(std::vector<CollisionInformation>& collisionInformations, const std::vector<std::shared_ptr<PhysicsEntity>>& physicsEntites) const;
		void ResolveContacts(const Real deltaTime, std::vector<CollisionInformation>& collisionInformations);
	};
}

#endif

