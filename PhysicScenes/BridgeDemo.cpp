#include <pch.h>
#include <PhysicScenes/BridgeDemo.h>
#include <DirectXTK/Components/MeshComponent.h>

void BridgeScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
{
    for (const auto& physicsObject : m_PlayerParticles)
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
    if (m_HasCreatedPlayerParticle)
    {
        m_TimerBeforeAnotherBullet += deltaTime;
        if (m_TimerBeforeAnotherBullet > BULLET_BURST_TIME)
        {
            m_TimerBeforeAnotherBullet = 0.f;
            m_HasCreatedPlayerParticle = false;
        }

        return;
    }

    if (!mouseState.leftButton)
    {
        return;
    }

    CreatePlayerParticle(deviceContext);
}

void BridgeScene::HandleKeyboardEvent(const float deltaTime, const DirectX::Keyboard::State keyboardState, ID3D11DeviceContext1& deviceContext)
{
    if (keyboardState.Right)
    {
        for (const auto playerParticle : m_PlayerParticles)
        {
            Aguamenti::ParticleComponent* particleComponent = Aguamenti::GetComponent<Aguamenti::ParticleComponent>(*playerParticle);
            assert(particleComponent != nullptr);

            particleComponent->m_CurrentPosition += Aguamenti::Vector3(0.001, 0, 0);
        }
    }
}

void BridgeScene::CreateBridgeParticle(const Aguamenti::Vector3 position, ID3D11DeviceContext1& deviceContext)
{
    std::shared_ptr<Aguamenti::PhysicsEntity> physicsEntity = std::make_shared<Aguamenti::PhysicsEntity>();
    Aguamenti::AddComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    Aguamenti::ParticleComponent* particleComponent = GetComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    assert(particleComponent != nullptr);
    particleComponent->m_InverseMass = 0;
    particleComponent->m_Velocity = Aguamenti::Vector3(0.f, 0.f, 0.f);
    particleComponent->m_Acceleration = Aguamenti::Vector3(0.f, 0, 0.f);
    particleComponent->m_Damping = 0;
    particleComponent->m_CurrentPosition = Aguamenti::Vector3(-0.1f, 0.f, 0.f);

    AddMeshComponent(*physicsEntity, BRIDGE_PARTICLE_DIAMETER, deviceContext);

    m_BridgeParticles.push_back(physicsEntity);
}

void BridgeScene::CreatePlayerParticle(ID3D11DeviceContext1& deviceContext)
{
    std::shared_ptr<Aguamenti::PhysicsEntity> physicsEntity = std::make_shared<Aguamenti::PhysicsEntity>();
    Aguamenti::AddComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    Aguamenti::ParticleComponent* particleComponent = GetComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    assert(particleComponent != nullptr);
    particleComponent->m_InverseMass = 32.f;
    particleComponent->m_Velocity = Aguamenti::Vector3(0.f, 0.f, 0.f);
    particleComponent->m_Acceleration = Aguamenti::Vector3(0.f, 0, 0.f);
    particleComponent->m_Damping = 0.99f;
    particleComponent->m_CurrentPosition = Aguamenti::Vector3(-1.f, 0.f, 0.f);

    AddMeshComponent(*physicsEntity, PLAYER_PARTICLE_DIAMETER, deviceContext);

    m_PlayerParticles.push_back(physicsEntity);
}

void BridgeScene::AddMeshComponent(Aguamenti::PhysicsEntity& physicsEntity, const Aguamenti::Real sphereDiameter, ID3D11DeviceContext1& deviceContext)
{
    Aguamenti::AddComponent<Aguamenti::MeshComponent>(physicsEntity);
    Aguamenti::MeshComponent* meshComponent = GetComponent<Aguamenti::MeshComponent>(physicsEntity);
    meshComponent->m_DXTK_GeometrixPrimitive = std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, sphereDiameter));
}
