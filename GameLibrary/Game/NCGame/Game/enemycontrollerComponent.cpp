#include "enemycontrollerComponent.h"
#include "kinematicComponent.h"



void enemycontrollerComponent::Create(float speed)
{
	m_speed = speed;
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
}
