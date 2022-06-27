#ifndef AGUAMENTI_GRAVITYFORCE_H
#define AGUAMENTI_GRAVITYFORCE_H

#include <Physics/Forces/Force.h>
#include <Physics/Core.h>

namespace Aguamenti
{
	class GravityForce : public Force
	{
	public:
		GravityForce(const Vector3 gravity)
			: m_Gravity(gravity)
		{

		}

	public:
		virtual void ApplyForce(ParticleComponent& particle) override;

	private:
		Vector3 m_Gravity;
	};
}

#endif
