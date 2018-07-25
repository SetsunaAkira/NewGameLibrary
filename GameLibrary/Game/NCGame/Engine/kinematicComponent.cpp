#include "kinematicComponent.h"
#include "timer.h"

void kinematicComponent::Create(float velocityMax, float dampening, bool enableGravity)
{
	m_velocityMax = velocityMax;
	m_dampening = dampening;
	m_enableGravity = enableGravity;

	m_forcetype = eForceType::FORCE;
	m_force = Vector2D::zero;
	m_velocity = Vector2D::zero;
}

void kinematicComponent::Destroy()
{
}

void kinematicComponent::ApplyForce(const Vector2D & force, eForceType forceType)
{
	float dt = Timer::Instance()->DeltaTimer();
}
