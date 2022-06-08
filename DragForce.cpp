#include "pch.h"
#include "DragForce.h"

void Aguamenti::DragForce::ApplyForce(Particle& particle)
{
	Aguamenti::Vector3 dragForce = particle.m_Velocity;
	const Aguamenti::Real velocityParticle = particle.m_Velocity.GetMagnitude();
	const Aguamenti::Real dragCoefficient = (velocityParticle * m_DragForceCoeficientK1) + velocityParticle * velocityParticle * m_DragForceCoeficientK2;
	dragForce.GetNormalize();
	dragForce *= -dragCoefficient;
	particle.AddForce(dragForce);
}
