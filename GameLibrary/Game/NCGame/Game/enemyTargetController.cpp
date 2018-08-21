#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "vector2D.h"
#include "entity.h"
#include "timer.h"
#include "missile.h"
#include "_math.h"
#include "enemyTargetController.h"
#include "debugdraw.h"



void EnemyTargetController::Create(const Vector2D& target, float speed)
{
	m_speed = speed;
	m_target = target;
}

void EnemyTargetController::Destroy()
{
}

void EnemyTargetController::Update()
{
	float dt = Timer::Instance()->DeltaTimer();

	Vector2D direction = m_target - m_sensei->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees);
	m_sensei->GetTransform().rotation = Math::Lerp(m_sensei->GetTransform().rotation, rotation, 5.0f * dt);

	Vector2D force = Vector2D::Rotate(Vector2D::up, m_sensei->GetTransform().rotation * Math::DegreesToRadians);

	DEBUG_DRAW_LINE(m_sensei->GetTransform().position, m_sensei->GetTransform().position + force * 200.0f, Color::cyan);


	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}

	DEBUG_DRAW_CROSS(m_target, Vector2D(20.0f, 20.0f), Color::white);

}
