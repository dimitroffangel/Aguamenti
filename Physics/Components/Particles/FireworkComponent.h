#ifndef AGUAMENTI_FIREWORK_H
#define AGUAMENTI_FIREWORK_H

#include <Component.h>

namespace Aguamenti
{
	class FireworkComponent : public Component
	{
	public:
		void Update(const Real deltaTime)
		{
			m_Age -= deltaTime;
		}

	public:
		Real m_Age;
		int m_NumberOfHeirs;
	};
}

#endif

