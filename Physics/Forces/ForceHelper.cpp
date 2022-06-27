#include <pch.h>

#include <Physics/Forces/ForceHelper.h>
#include <Physics/Forces/GravityForce.h>

void Aguamenti::AddRelativeGravitationalForce(RelativeForceComponent& relativeComponent)
{
	relativeComponent.m_Forces.push_back(std::make_shared<GravityForce>(Vector3(0, -0.002f, 0)));
}
