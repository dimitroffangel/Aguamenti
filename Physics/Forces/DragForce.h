#ifndef AGUAMENTI_DRAGFORCE_H
#define AGUAMENTI_DRAGFORCE_H

#include <Physics/Forces/Force.h>
#include <Physics/Core.h>

namespace Aguamenti
{
	class DragForce : public Force
	{
	public:
		DragForce(const Real k1, const Real k2)
			: m_DragForceCoeficientK1(k1), m_DragForceCoeficientK2(k2)
		{

		}

	public:
		virtual void ApplyForce_Internal(const Real deltaTime, ParticleComponent& particle) override;

	private:
		Real m_DragForceCoeficientK1;
		Real m_DragForceCoeficientK2;
	};
}

#endif
