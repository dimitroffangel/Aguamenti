#ifndef AGUAMENTI_SPRINGPARTCLEFORCE_H
#define AGUAMENTI_SPRINGPARTCLEFORCE_H

#include <Physics/Forces/Force.h>

namespace Aguamenti
{
	class SpringAnchoredForce : public Force
	{
	public:
		SpringAnchoredForce(const Real springCoefficient, const Real springLengthAtRest)
			: m_SpringCoefficient(springCoefficient), m_SpringLengthAtRest(springLengthAtRest)
		{

		}

	public:
		virtual void ApplyForce(Particle& particle) override;

	private:
		Real m_SpringCoefficient;
		Real m_SpringLengthAtRest;
		Vector3 m_SpringLocation;
	};
}

#endif