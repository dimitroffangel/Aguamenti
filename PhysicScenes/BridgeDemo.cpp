#include <pch.h>
#include <PhysicScenes/BridgeDemo.h>
#include <DirectXTK/Components/MeshComponent.h>

void BridgeScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
{
    for (const auto& physicsObject : m_Particles)
    {
        Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*physicsObject);
        assert(particleComponent != nullptr);
        const auto& particleMesh = Aguamenti::GetComponent<Aguamenti::MeshComponent>(*physicsObject);
        const DirectX::SimpleMath::Matrix particleMeshPosition = DirectX::SimpleMath::Matrix::CreateTranslation(
            DirectX::SimpleMath::Vector3(particleComponent->m_CurrentPosition.m_X, particleComponent->m_CurrentPosition.m_Y, particleComponent->m_CurrentPosition.m_Z));
        particleMesh->m_DXTK_GeometrixPrimitive->Draw(particleMeshPosition, matrixView, matrixProjection);
    }
}

void BridgeScene::HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext)
{
}
