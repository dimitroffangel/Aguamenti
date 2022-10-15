#ifndef AGUAMENTI_FORCEHELPER_H
#define AGUAMENTI_FORCEHELPER_H

#include <Physics/Systems/Entity/PhysicsEntityHelper.h>
#include <Physics/Core.h>
#include <Physics/Components/Particles/Particle.h>
#include <Physics/Entity/CollisionInformation.h>

namespace Aguamenti
{
	bool CalculateSeparatingVelocity(CollisionInformation& collisionInformation);
	void ResolveContact(const Real deltaTime, const CollisionInformation& collisionInformation);
	void ResolveInterpenetration(const Real deltaTime, const CollisionInformation& collisionInformation);
}


#endif