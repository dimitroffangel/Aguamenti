#ifndef AGUAMENTI_PHYSICSENTITYHELPER_H
#define AGUAMENTI_PHYSICSENTITYHELPER_H

class Component;

#include <iostream>
#include <Component.h>
#include <Physics/Entity/PhysicsEntity.h>

namespace Aguamenti
{
	static void GetType(const Component* component)
	{
		if (component == nullptr)
		{
			return;
		}

		std::cout << component << " " << typeid(*component).hash_code() << '\n';
	}

	static bool CompareType(const Component* lhs, const Component* rhs)
	{
		if (lhs == nullptr || rhs == nullptr)
		{
			return false;
		}

		return typeid(*lhs).hash_code() == typeid(*rhs).hash_code();
	}

	template<typename T>
	bool HasComponent(const std::vector<std::unique_ptr<Component>>& components)
	{
		for (const auto& component : components)
		{
			const size_t componentNameHashCode = typeid(*component).hash_code();

			if (typeid(T).hash_code() == componentNameHashCode)
				return true;
		}

		return false;
	}

	template<typename T>
		requires std::derived_from<T, Component>
	bool AddComponent(PhysicsEntity& physicsEntity)
	{
		if (HasComponent<T>(physicsEntity.m_Components))
		{
			return false;
		}

		std::unique_ptr<Component> component = std::make_unique<T>();
		physicsEntity.m_Components.push_back(std::move(component));
		return true;
	}

	template<typename T>
		requires std::derived_from<T, Component>
	T* GetComponent(const PhysicsEntity& physicsEntity)
	{
		if (!HasComponent<T>(physicsEntity.m_Components))
		{
			return nullptr;
		}

		for (auto& component : physicsEntity.m_Components)
		{
			const size_t componentNameHashCode = typeid(*component).hash_code();

			if (typeid(T).hash_code() == componentNameHashCode)
				return static_cast<T*>(component.get());
		}
	}
}

#endif
