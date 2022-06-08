#ifndef AGUAMENTI_GRAVITYFORCE_H
#define AGUAMENTI_GRAVITYFORCE_H

#include "Force.h"
#include "Core.h"

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
		virtual void ApplyForce(Particle& particle) override;

	private:
		Vector3 m_Gravity;
	};
}

#endif
