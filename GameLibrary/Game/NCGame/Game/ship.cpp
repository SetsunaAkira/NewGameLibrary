#include "ship.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include <iostream>

void Ship::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	
	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	ShipControllerComponent* shipcontroller = addComponent<ShipControllerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = addComponent<AABBComponent>();
	aabbComponent->Create();

	std::cout << "ship stuff made" << std::endl;
}

void Ship::Update()
{
	Entity::Update();
	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
}

void Ship::OnEvent(const Event & event)
{
	if (event.EventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			//SetState(Entity::DESTROY);
		}
	}
}
