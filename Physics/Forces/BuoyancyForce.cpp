#include <pch.h>

#include <Physics/Forces/BuoyancyForce.h>

void Aguamenti::BuoyancyForce::ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle)
{
	const Real depth = particle.m_CurrentPosition.m_Y;
	if (depth >= m_LiquidHeight + m_MaxSubmersionDepth)
	{
		return;
	}

	Vector3 forceToApply(0, 0, 0);

	if (depth <= m_LiquidHeight - m_MaxSubmersionDepth)
	{
		forceToApply.m_Y = m_LiquidDensity * m_Volume;
	}
	else
	{
		forceToApply.m_Y = m_LiquidDensity * m_Volume * (depth - m_LiquidHeight - m_MaxSubmersionDepth) / (2 * m_MaxSubmersionDepth);
	}
	particle.AddForce(forceToApply);
}
