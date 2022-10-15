#ifndef AGUAMENTI_COLLISIONRESOLVER_H
#define AGUAMENTI_COLLISIONRESOLVER_H

#include <CollisionInformation.cpp>
#include <Physics/Entity/PhysicsEntity.h>

namespace Aguamenti
{
	class CollisionResolver
	{
	private:
		size_t m_MaxNumberOfIterations;
		size_t m_CurrentNumberOfIterations;

	public:
		void GatherCollisions(std::vector<CollisionInformation>& collisionInformations, const std::vector<std::shared_ptr<PhysicsEntity>>& physicsEntites) const;
		void ResolveContacts(const Real deltaTime, std::vector<CollisionInformation>& collisionInformations);
	};
}

#endif

