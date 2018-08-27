#include "transformcontrollercomponent.h"
#include "kinematicComponent.h"
#include "vector2D.h"
#include "entity.h"
#include "timer.h"


void TransformControllerComponent::Create(const Vector2D & position, float rotation, float speed, float rotaterate)
{
	m_position = position;
	m_rotation = rotation;
	m_speed = speed;
	m_rotateRate = rotaterate;
}

void TransformControllerComponent::Destroy()
{
}

void TransformControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTimer();

	Vector2D direction = m_position - m_sensei->GetTransform().position;
	m_sensei->GetTransform().rotation = Math::LerpDegrees(m_sensei->GetTransform().rotation, m_rotation, m_rotateRate * dt);

	Vector2D force = direction.Normalized();
	float speedMulti = Math::Clamp01(direction.Length() / 32.0f);
	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * (m_speed * speedMulti), kinematicComponent::VELOCITY);
	}

}
