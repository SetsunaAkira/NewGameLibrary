#include "enemycontrollerComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "Math.h"



void enemycontrollerComponent::Create(float speed)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(1.0f, 3.0f);
}

void enemycontrollerComponent::Destroy()
{
}

void enemycontrollerComponent::Update()
{
	Vector2D force = Vector2D::up;
	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::FORCE);
	}

	float dt = Timer::Instance()->DeltaTimer();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		m_timer = Math::GetRandomRange(1.0f, 3.0f);
	}
}
