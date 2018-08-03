#include "missile.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"
#include "timer.h"

void Missile::Create(const Vector2D & position, const Vector2D &  direction, float speed)
{
	m_lifetime = 2.0f;
	SetTag("playermissle");
	
	m_transform.position = position;

	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);
	kinematic->ApplyForce(direction * speed, kinematicComponent::FORCE);


	ShipControllerComponent* shipcontroller = addComponent<ShipControllerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\missile.png");
}

void Missile::Update()
{
	Entity::Update();
	m_lifetime = m_lifetime - Timer::Instance()->DeltaTimer();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}
}
