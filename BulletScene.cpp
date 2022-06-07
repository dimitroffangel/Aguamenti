#include "pch.h"
#include "BulletScene.h"
#include "Particle.h"

#include <algorithm>

void BulletScene::AddParticle(ID3D11DeviceContext1& deviceContext, const Aguamenti::Real spawnPositionX, const Aguamenti::Real spawnPositionY)
{
    Particle particle;
    particle.m_InverseMass = 32.f;
    particle.m_Velocity = Aguamenti::Vector3(0.3f, 0.f, 0.f);
    particle.m_Acceleration = Aguamenti::Vector3(2.f, 0, 0.f);
    particle.m_Damping = 0.99f;
    particle.m_CurrentPosition = Aguamenti::Vector3(spawnPositionX, spawnPositionY, 0.f);

    m_Particles.push_back(particle);
    m_ParticlesMeshes.push_back(std::move(DirectX::GeometricPrimitive::CreateSphere(&deviceContext, 0.1f)));
}

void BulletScene::UpdatePhysicsObjects(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext)
{
    ApplyGravity();

    for (Particle& particle : m_Particles)
    {
        particle.Integrate(deltaTime);
    }
}

void BulletScene::DrawPhysicsObjects(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection)
{
    assert(m_Particles.size() == m_ParticlesMeshes.size());

    for (size_t i = 0; i < m_ParticlesMeshes.size(); ++i)
    {
        const auto& particleMesh = m_ParticlesMeshes[i];
        const DirectX::SimpleMath::Matrix particleMeshPosition = DirectX::SimpleMath::Matrix::CreateTranslation(
            DirectX::SimpleMath::Vector3(m_Particles[i].m_CurrentPosition.m_X, m_Particles[i].m_CurrentPosition.m_Y, m_Particles[i].m_CurrentPosition.m_Z));
        particleMesh->Draw(particleMeshPosition, matrixView, matrixProjection);
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

void BulletScene::ApplyGravity()
{
    for (Particle& particle : m_Particles)
    {
        particle.AddForce(m_Gravity);
    }
}
