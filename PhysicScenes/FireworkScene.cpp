#include <pch.h>

#include <PhysicScenes/FireworkScene.h>

#include <Physics/Systems/Forces/ForceHelper.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

#include <Physics/Components/RelativeForceComponent.h>

#include <DirectXTK/Components/MeshComponent.h>

#include <algorithm>

void FireworkScene::UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext)
{
	Aguamenti::ApplyForce(m_Forces, m_Fireworks);

	const size_t currentNumberOfFireworksBeforeUpdate = m_Fireworks.size();
	for (size_t i = 0; i < currentNumberOfFireworksBeforeUpdate; ++i)
	{
		const auto& firework = m_Fireworks[i];
		Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*firework);
		assert(particleComponent != nullptr);
		particleComponent->Update(deltaTime);

		Aguamenti::FireworkComponent* fireworkComponent = Aguamenti::GetComponent<Aguamenti::FireworkComponent>(*firework);
		assert(fireworkComponent != nullptr);
		fireworkComponent->Update(deltaTime);

		if (Aguamenti::RelativeForceComponent* relativeForceComponent = Aguamenti::GetComponent<Aguamenti::RelativeForceComponent>(*firework))
		{
			relativeForceComponent->ApplyForces(*firework);
		}

		if (fireworkComponent->m_Age <= 0)
		{
			if (m_Fireworks.size() < MAXIMUM_NUMBER_OF_FIREWORKS)
			{
				CreateFirework(*firework, deviceContext);
			}
		}
	}

	m_Fireworks.erase(std::remove_if(m_Fireworks.begin(), m_Fireworks.end(), 
		[](const std::shared_ptr<Aguamenti::PhysicsEntity>& firework) {
			Aguamenti::FireworkComponent* fireworkComponent = Aguamenti::GetComponent<Aguamenti::FireworkComponent>(*firework);
			assert(fireworkComponent != nullptr);
			return fireworkComponent->m_Age <= 0.f;
		}), 
		m_Fireworks.end());
}

void FireworkScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
{
	for (const auto& physicsObject : m_Fireworks)
	{
		Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*physicsObject);
		assert(particleComponent != nullptr);
		const auto& particleMesh = Aguamenti::GetComponent<Aguamenti::MeshComponent>(*physicsObject);
		const DirectX::SimpleMath::Matrix particleMeshPosition = DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3(particleComponent->m_CurrentPosition.m_X, particleComponent->m_CurrentPosition.m_Y, particleComponent->m_CurrentPosition.m_Z));
		particleMesh->m_DXTK_GeometrixPrimitive->Draw(particleMeshPosition, matrixView, matrixProjection);
	}
}

void FireworkScene::HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext)
{
	if (m_HasSpawnedFireworks)
	{
		m_TimerBeforeAnotherFireworkSet += deltaTime;
		if (m_TimerBeforeAnotherFireworkSet > 1.f)
		{
			m_TimerBeforeAnotherFireworkSet = 0.f;
			m_HasSpawnedFireworks = false;
		}

		return;
	}

	if (mouseState.leftButton)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			std::shared_ptr<Aguamenti::PhysicsEntity> physicsEntity = std::make_shared<Aguamenti::PhysicsEntity>();

			Aguamenti::AddComponent<Aguamenti::ParticleComponent>(*physicsEntity);
			Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*physicsEntity);
			assert(particleComponent != nullptr);
			particleComponent->m_InverseMass = 32.f;
			particleComponent->m_Velocity = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
			particleComponent->m_Acceleration = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.01, 0.01), Aguamenti::GetRandomRealNumber(-0.01, 0.01), 0.f);
			particleComponent->m_Damping = 0.99f;
			particleComponent->m_CurrentPosition = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
			
			Aguamenti::AddComponent<Aguamenti::FireworkComponent>(*physicsEntity);
			Aguamenti::FireworkComponent* fireworkComponent = Aguamenti::GetComponent<Aguamenti::FireworkComponent>(*physicsEntity);
			assert(fireworkComponent != nullptr);
			fireworkComponent->m_NumberOfHeirs = 3;
			fireworkComponent->m_Age = Aguamenti::GetRandomRealNumber(1.0, 3.0);

			Aguamenti::AddComponent<Aguamenti::MeshComponent>(*physicsEntity);
			Aguamenti::MeshComponent* meshComponent = Aguamenti::GetComponent<Aguamenti::MeshComponent>(*physicsEntity);
			meshComponent->m_DXTK_GeometrixPrimitive =  std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.05f));
			assert(meshComponent != nullptr);

			m_Fireworks.push_back(physicsEntity);
		}
		m_HasSpawnedFireworks = true;
	}
}

void FireworkScene::CreateFirework(const Aguamenti::PhysicsEntity& physicsEntity, ID3D11DeviceContext1& deviceContext)
{
	const Aguamenti::FireworkComponent* fireworkComponent = Aguamenti::GetComponent<Aguamenti::FireworkComponent>(physicsEntity);
	assert(fireworkComponent != nullptr);

	for (int i = 0; i < fireworkComponent->m_NumberOfHeirs; ++i)
	{
		std::shared_ptr<Aguamenti::PhysicsEntity> childPhysicsEntity = std::make_shared<Aguamenti::PhysicsEntity>();

		const Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(physicsEntity);
		assert(particleComponent != nullptr);
		Aguamenti::AddComponent<Aguamenti::ParticleComponent>(*childPhysicsEntity);
		Aguamenti::ParticleComponent* childParticleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*childPhysicsEntity);
		assert(childParticleComponent != nullptr);
		childParticleComponent->m_Velocity = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
		childParticleComponent->m_Acceleration = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.01, 0.01), Aguamenti::GetRandomRealNumber(-0.01, 0.01), 0.f);
		childParticleComponent->m_CurrentPosition = particleComponent->m_CurrentPosition;
		childParticleComponent->m_AccumulatedForce = particleComponent->m_AccumulatedForce;
		childParticleComponent->m_Damping = particleComponent->m_Damping;
		childParticleComponent->m_InverseMass = particleComponent->m_InverseMass;

		Aguamenti::AddComponent<Aguamenti::FireworkComponent>(*childPhysicsEntity);
		Aguamenti::FireworkComponent* childFireworkComponent = Aguamenti::GetComponent<Aguamenti::FireworkComponent>(*childPhysicsEntity);
		assert(childFireworkComponent != nullptr);
		childFireworkComponent ->m_Age = Aguamenti::GetRandomRealNumber(0.1f, 3.f);
		childFireworkComponent ->m_NumberOfHeirs = Aguamenti::GetRandomIntegerNumber(0, 5);

		Aguamenti::AddComponent<Aguamenti::MeshComponent>(*childPhysicsEntity);
		Aguamenti::MeshComponent* childMeshComponent = Aguamenti::GetComponent<Aguamenti::MeshComponent>(*childPhysicsEntity);
		assert(childMeshComponent != nullptr);
		childMeshComponent->m_DXTK_GeometrixPrimitive = std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.05f));
		
		Aguamenti::AddComponent<Aguamenti::RelativeForceComponent>(*childPhysicsEntity);
		Aguamenti::RelativeForceComponent* childRelativeForceComponent = Aguamenti::GetComponent<Aguamenti::RelativeForceComponent>(*childPhysicsEntity);
		assert(childRelativeForceComponent != nullptr);
		Aguamenti::AddRelativeGravitationalForce(*childRelativeForceComponent);

		m_Fireworks.push_back(childPhysicsEntity);
	}
}
