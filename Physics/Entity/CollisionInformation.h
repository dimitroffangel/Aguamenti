#ifndef AGUAMENTI_COLLISIONINFORMATION_H
#define AGUAMENTI_COLLISIONINFORMATION_H

#include <Physics/Core.h>

class PhysicsEntity;

namespace Aguamenti
{
	const Real RESTITUTION_DEFAULT = -0.75;

	struct CollisionInformation
	{
		std::weak_ptr<PhysicsEntity> m_LhsPhysicsEntity;
		std::weak_ptr<PhysicsEntity> m_RhsPhysicsEntity;
		Vector3 m_ContactNormal;
		Real m_SeparationVelocity;
		Real m_Restituion = RESTITUTION_DEFAULT;
		Real m_PenetrationLength;
	};
}

#endif