#ifndef AGUAMENTI_BUOYANCYFORCE_H
#define AGUAMENTI_BUOYANCYFORCE_H

#include <Physics/Forces/Force.h>

namespace Aguamenti
{
	class BuoyancyForce : public Force
	{
	public:
		BuoyancyForce(const Real sumbersionDepth, const Real volume, const Real liquidHeight, const Real liquidDensity = 1000.f)
			: m_MaxSubmersionDepth(sumbersionDepth), m_Volume(volume), m_LiquidHeight(liquidHeight), m_LiquidDensity(liquidDensity)
		{

		}

	private:
		// Inherited via Force
		virtual void ApplyForce_Internal(ParticleComponent& particle) override;

	private:
		Real m_MaxSubmersionDepth;
		Real m_Volume;
		Real m_LiquidHeight;
		Real m_LiquidDensity;
	};
}

#endif