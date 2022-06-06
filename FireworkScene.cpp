#include "pch.h"
#include "FireworkScene.h"

#include <algorithm>

void FireworkScene::UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext)
{
	const size_t currentNumberOfFireworksBeforeUpdate = m_Fireworks.size();
	for (size_t i = 0; i < currentNumberOfFireworksBeforeUpdate; ++i)
	{
		Firework& firework = m_Fireworks[i];
		firework.Integrate(deltaTime);
		firework.Update(deltaTime);

		if (firework.m_Age <= 0)
		{
			m_FireworkMeshes.pop_back();

			if (m_Fireworks.size() < MAXIMUM_NUMBER_OF_FIREWORKS)
			{
				CreateFirework(firework, deviceContext);
			}
		}
	}

	m_Fireworks.erase(std::remove_if(m_Fireworks.begin(), m_Fireworks.end(), 
		[](const Firework& firework) {
				return firework.m_Age <= 0.f;
		}), 
		m_Fireworks.end());
}

void FireworkScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
{
	assert(m_Fireworks.size() == m_FireworkMeshes.size());

	for (size_t i = 0; i < m_FireworkMeshes.size(); ++i)
	{
		const auto& fireworkMesh = m_FireworkMeshes[i];
		const DirectX::SimpleMath::Matrix particleMeshPosition = DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3(m_Fireworks[i].m_CurrentPosition.m_X, m_Fireworks[i].m_CurrentPosition.m_Y, m_Fireworks[i].m_CurrentPosition.m_Z));
		fireworkMesh->Draw(particleMeshPosition, matrixView, matrixProjection);
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
			Firework particle;
			particle.m_InverseMass = 32.f;
			
			particle.m_Velocity = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
			particle.m_Acceleration = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.01, 0.01), Aguamenti::GetRandomRealNumber(-0.01, 0.01), 0.f);
			particle.m_Damping = 0.99f;
			particle.m_CurrentPosition = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
			particle.m_NumberOfHeirs = 3;
			particle.m_Age = Aguamenti::GetRandomRealNumber(1.0, 3.0);

			m_Fireworks.push_back(particle);
			m_FireworkMeshes.push_back(std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.05f)));
		}
		m_HasSpawnedFireworks = true;
	}
}

void FireworkScene::CreateFirework(const Firework& firework, ID3D11DeviceContext1& deviceContext)
{
	for (int i = 0; i < firework.m_NumberOfHeirs; ++i)
	{
		Firework childFirework = firework;
		childFirework.m_Age = Aguamenti::GetRandomRealNumber(0.1f, 3.f);
		childFirework.m_NumberOfHeirs = Aguamenti::GetRandomIntegerNumber(0, 5);
		childFirework.m_Velocity = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.1, 0.1), Aguamenti::GetRandomRealNumber(-0.1, 0.1), 0.f);
		childFirework.m_Acceleration = Aguamenti::Vector3(Aguamenti::GetRandomRealNumber(-0.01, 0.01), Aguamenti::GetRandomRealNumber(-0.01, 0.01), 0.f);

		m_Fireworks.push_back(childFirework);
		m_FireworkMeshes.push_back(std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.05f)));
	}
}
