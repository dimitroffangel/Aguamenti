#ifndef AGUAMENTI_PHYSICSENTITY_H
#define AGUAMENTI_PHYSICSENTITY_H

class Component;

namespace Aguamenti
{
	class PhysicsEntity
	{
	public:
		size_t m_ID;
		std::vector<std::unique_ptr<Component>> m_Components;
	};
}
#endif