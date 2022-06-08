#include "pch.h"
#include "PhysicsScene.h"

#include "GravityForce.h"
#include "DragForce.h"

void PhysicsScene::AddGravitationalForce(const Aguamenti::Vector3 gravity)
{
	std::unique_ptr<Aguamenti::Force> gravityForce = std::make_unique<Aguamenti::GravityForce>(gravity);
	m_Forces.push_back(std::move(gravityForce));
}

void PhysicsScene::AddDragForce(const Aguamenti::Real k1, const Aguamenti::Real k2)
{
	std::unique_ptr<Aguamenti::Force> dragForce = std::make_unique<Aguamenti::DragForce>(k1, k2);
	m_Forces.push_back(std::move(dragForce));
}
