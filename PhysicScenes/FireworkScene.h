#ifndef AGUAMENTI_FIREWORKSCENE_H
#define AGUAMENTI_FIREWORKSCENE_H

#include <PhysicScenes/PhysicsScene.h>
#include <Physics/Components/Particles/FireworkComponent.h>
#include <Physics/Entity/PhysicsEntity.h>

class FireworkScene : public PhysicsScene
{
	static constexpr size_t MAXIMUM_NUMBER_OF_FIREWORKS = 800;

public:
	virtual void UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext) override;
	virtual void DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection) override;
	virtual void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext) override;
	
private:
	void CreateFirework(const Aguamenti::PhysicsEntity& physicsEntity,  ID3D11DeviceContext1& deviceContext);

private:
	Aguamenti::Real m_TimerBeforeAnotherFireworkSet = 0.0f;
	bool m_HasSpawnedFireworks = false;
	std::vector<std::shared_ptr<Aguamenti::PhysicsEntity>> m_Fireworks;
};

#endif