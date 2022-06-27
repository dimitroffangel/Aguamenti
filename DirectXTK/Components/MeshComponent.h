#ifndef AGUAMENTI_MESHCOMPONENT_H
#define AGUAMENTI_MESHCOMPONENT_H

#include <Component.h>

namespace Aguamenti
{
	class MeshComponent : public Aguamenti::Component
	{
	public:
		// Inherited via Component
		virtual void Update(const Real deltaTime) override;

	public:
		std::unique_ptr<DirectX::GeometricPrimitive> m_DXTK_GeometrixPrimitive;
	};
}

#endif