#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "vector2D.h"
#include "entity.h"
#include "timer.h"
#include "missile.h"
#include "_math.h"



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

	Entity* player = m_sensei->Getscene()->GetEntityWithID("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_sensei->GetTransform().position.x;
		if (dx < -32.0f) force.x = -0.7f;
		if (dx >  32.0f) force.x = 0.7f;
	}

	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}

	float dt = Timer::Instance()->DeltaTimer();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

		Missile* missile = new Missile(m_sensei->Getscene());
		missile->Create("enemymissile", m_sensei->GetTransform().position, Vector2D::up, 800.0f);
		m_sensei->Getscene()->AddEntity(missile);
	}
}
