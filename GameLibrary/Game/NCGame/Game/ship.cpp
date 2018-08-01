#include "ship.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"

void Ship::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	
	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);


	shipcontrollerComponent* shipcontroller = addComponent<shipcontrollerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));


}
