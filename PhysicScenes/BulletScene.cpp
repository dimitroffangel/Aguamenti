#include <pch.h>

#include <PhysicScenes/BulletScene.h>

#include <Physics/Components/Particles/Particle.h>

#include <Physics/Systems/Forces/ForceHelper.h>
#include <Physics/Systems/Entity/PhysicsEntityHelper.h>

#include <DirectXTK/Components/MeshComponent.h>

#include <algorithm>

void BulletScene::AddParticle(ID3D11DeviceContext1& deviceContext, const Aguamenti::Real spawnPositionX, const Aguamenti::Real spawnPositionY)
{
    std::shared_ptr<Aguamenti::PhysicsEntity> physicsEntity = std::make_shared<Aguamenti::PhysicsEntity>();
    Aguamenti::AddComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    Aguamenti::ParticleComponent* particleComponent = GetComponent<Aguamenti::ParticleComponent>(*physicsEntity);
    assert(particleComponent != nullptr);
    particleComponent->m_InverseMass = 32.f;
    particleComponent->m_Velocity = Aguamenti::Vector3(0.3f, 0.f, 0.f);
    particleComponent->m_Acceleration = Aguamenti::Vector3(2.f, 0, 0.f);
    particleComponent->m_Damping = 0.99f;
    particleComponent->m_CurrentPosition = Aguamenti::Vector3(spawnPositionX, spawnPositionY, 0.f);

    Aguamenti::AddComponent<Aguamenti::MeshComponent>(*physicsEntity);
    Aguamenti::MeshComponent* meshComponent = GetComponent<Aguamenti::MeshComponent>(*physicsEntity);
    meshComponent->m_DXTK_GeometrixPrimitive = std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.1f));

    m_Particles.push_back(physicsEntity);
}

void BulletScene::UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext)
{
    Aguamenti::ApplyForce(deltaTime, m_Forces, m_Particles);

    for (const std::shared_ptr<Aguamenti::PhysicsEntity>& physicsEntity : m_Particles)
    {
        Aguamenti::ParticleComponent* particleComponent = GetComponent<Aguamenti::ParticleComponent>(*physicsEntity);
        assert(particleComponent != nullptr);
        particleComponent->Update(deltaTime);
    }
}

void BulletScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
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

void BulletScene::HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext)
{
    if (m_HasFiredBullet)
    {
        m_TimerBeforeAnotherBullet += deltaTime;
        if (m_TimerBeforeAnotherBullet > BULLET_BURST_TIME)
        {
            m_TimerBeforeAnotherBullet = 0.f;
            m_HasFiredBullet = false;
        }

        return;
    }

    if (mouseState.leftButton)
    {
        AddParticle(deviceContext, -1.f, 0.f);
        m_HasFiredBullet = true;
    }
}