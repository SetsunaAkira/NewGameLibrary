#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "audiosystem.h"
#include "eventmanager.h"

void Enemy::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SetTag("enemy");
	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	//ShipControllerComponent* shipController = AddComponent<ShipControllerComponent>();
	//shipController->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = addComponent<AABBComponent>();
	aabbComponent->Create();

	Audiosystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
}

void Enemy::Update()
{
	Entity::Update();
}

void Enemy::OnEvent(const Event & event)
{
	if (event.EventID == "collision")
	{
		if (event.sender->GetTag() == "playermissle")
		{
			Event _event;
			_event.EventID = "add_score";
			EventManager::Instance()->SendGameMessage(_event);
			SetState(Entity::DESTROY);
			Audiosystem::Instance()->PlaySound("explosion",false);
		}
	}
}
