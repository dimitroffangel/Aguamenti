#ifndef AGUAMENTI_COMPONENT_H
#define AGUAMENTI_COMPONENT_H

#include "Physics/Precision.h"

namespace Aguamenti
{
	class Component
	{
	public:
		virtual ~Component()
		{

		}

		virtual void Update(const Real deltaTime) = 0;
	};
}

#endif