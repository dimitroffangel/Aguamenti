#ifndef AGUAMENTI_PARTICLE_H
#define AGUAMENTI_PARTICLE_H

#include <Physics/Core.h>
#include <Physics/Precision.h>
#include <Component.h>

namespace Aguamenti
{
	class ParticleComponent : public Component
	{
	public:
		ParticleComponent()
		{

		}

		ParticleComponent(const Vector3& initialPosition, const Vector3& velocity, const Vector3& acceleration, const Real damping, const Real inverseMass)
			: m_CurrentPosition(initialPosition), m_Velocity(velocity), m_Acceleration(acceleration), m_Damping(damping), m_InverseMass(inverseMass)

		{

		}

	public:
		Vector3 m_CurrentPosition;
		Vector3 m_Velocity;
		Vector3 m_Acceleration;
		Vector3 m_AccumulatedForce;

		Real m_Damping;
		Real m_InverseMass;

	public:
		void AddForce(const Vector3 forceToAdd);
		void Integrate(const Real deltaTime);

	private:
		void RemoveAllForcesApplied();

		// Inherited via Component
	public:
		virtual void Update(const Real deltaTime) override;
	};
}


#endif