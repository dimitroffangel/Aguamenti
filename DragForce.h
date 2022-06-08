#ifndef AGUAMENTI_DRAGFORCE_H
#define AGUAMENTI_DRAGFORCE_H

#include "Force.h"
#include "Core.h"

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
		virtual void ApplyForce(Particle& particle) override;

	private:
		Real m_DragForceCoeficientK1;
		Real m_DragForceCoeficientK2;
	};
}

#endif
