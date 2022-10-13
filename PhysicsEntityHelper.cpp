#include "pch.h"
#include <Physics/PhysicsEntityHelper.h>

#include <Component.h>

#include <iostream>

using namespace Aguamenti;

void Aguamenti::GetType(const Component* component)
{
	if (component == nullptr)
	{
		return;
	}

	std::cout << component << " " << typeid(*component).hash_code() << '\n';
}
