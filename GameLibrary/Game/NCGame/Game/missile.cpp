#include "missile.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"

void Missile::Create(const Vector2D & position, const Vector2D &  direction, float speed)
{
	
	m_transform.position = position;

	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);
	kinematic->ApplyForce(direction * speed, kinematicComponent::FORCE);


	shipcontrollerComponent* shipcontroller = addComponent<shipcontrollerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\missile.png");
}
