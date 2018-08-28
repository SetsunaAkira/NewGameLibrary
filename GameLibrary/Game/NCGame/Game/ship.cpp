#include "ship.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include <iostream>
#include "animationcomponent.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	
	kinematicComponent* kinematic = AddComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	ShipControllerComponent* shipcontroller = AddComponent<ShipControllerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 1.0f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create("player");
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
			SetState(Entity::DESTROY);
			Entity* explosion = new Entity(m_scene);
			explosion->GetTransform().position = Vector2D(400.0f, 300.0f);
			explosion->GetTransform().scale = Vector2D(2.0f, 2.0f);
			SpriteComponent* spriteComponent = explosion->AddComponent<SpriteComponent>();
			spriteComponent->Create("", Vector2D(0.5f, 0.5f));
			AnimationComponent* animationComponent = explosion->AddComponent<AnimationComponent>();
			std::vector<std::string> textureNames = { "ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png" };
			animationComponent->Create(textureNames, 1.0f / 10.0f);
			m_scene->AddEntity(explosion);
		}
	}
}
