#include "pch.h"
#include <Physics/Systems/CollisionResolver.h>
#include <Physics/Systems/CollisionHelper.h>
#include <queue>

void Aguamenti::CollisionResolver::ResolveContacts(const Real deltaTime, std::vector<CollisionInformation>& collisionInformations)
{
	auto collisionInformationComparator = [](const CollisionInformation& lhs, const CollisionInformation& rhs)
	{
		if (lhs.m_SeperationVelocity > rhs.m_SeperationVelocity)
		{
			return true;
		}

		return lhs.m_PenetrationLength > rhs.m_PenetrationLength;
	};

	std::priority_queue<CollisionInformation, std::vector<CollisionInformation>, decltype(collisionInformationComparator)>
		collisionsOrdered(collisionInformations.begin(), collisionInformations.end());
	m_CurrentNumberOfIterations = 0;
	while (!collisionsOrdered.empty() && m_CurrentNumberOfIterations < m_MaxNumberOfIterations)
	{
		const CollisionInformation& currentMaximumCollision = collisionsOrdered.top();

		++m_CurrentNumberOfIterations;
		Aguamenti::ResolveContact(deltaTime, currentMaximumCollision);
		Aguamenti::ResolveInterpenetration(deltaTime, currentMaximumCollision);

		collisionsOrdered.pop();
	}
}
