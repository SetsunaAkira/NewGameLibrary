#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"

void Enemy::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	//ShipControllerComponent* shipController = AddComponent<ShipControllerComponent>();
	//shipController->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));
}

void Enemy::Update()
{
	Entity::Update();
}