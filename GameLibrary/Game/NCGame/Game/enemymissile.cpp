#include "enemymissile.h"
#include "missile.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "timer.h"
#include "aabbComponent.h"

void EnemyMissile::Create(const ID & tag, const Vector2D & position, const Vector2D & direction, float speed)
{
	m_lifetime = 2.0f;
	SetTag(tag);

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	kinematicComponent* kinematic = AddComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.9f, false);
	kinematic->ApplyForce(direction * speed, kinematicComponent::VELOCITY);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();

	if (tag == "playermissile")	spriteComponent->Create("missile01.png", Vector2D(0.5f, 0.5f));
	else if (tag == "enemymissile")	spriteComponent->Create("missile02.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(tag, Vector2D(0.7f, 0.9f));
}

void EnemyMissile::Update()
{
	Entity::Update();
	m_lifetime = m_lifetime - Timer::Instance()->DeltaTimer();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}
}

void EnemyMissile::OnEvent(const Event & event)
{
	if (event.EventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" && m_tag == "playermissile")
		{
			SetState(Entity::DESTROY);
		}
		if (event.sender->GetTag() == "player" && m_tag == "enemymissile")
		{
			SetState(Entity::DESTROY);
		}
	}
}
