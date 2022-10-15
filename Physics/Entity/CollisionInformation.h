#ifndef AGUAMENTI_COLLISIONINFORMATION_H
#define AGUAMENTI_COLLISIONINFORMATION_H

#include <Physics/Core.h>

class ParticleComponent;

namespace Aguamenti
{
	const Real RESTITUTION_DEFAULT = -0.75;

	struct CollisionInformation
	{
		ParticleComponent* m_LhsParticleComponent;
		ParticleComponent* m_RhsParticleComponent;
		Vector3 m_ContactNormal;
		Real m_SeperationVelocity;
		Real m_Restituion = RESTITUTION_DEFAULT;
		Real m_PenetrationLength;
	};
}

#endif