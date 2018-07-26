#include "ship.h"
#include "transformComponent.h"
#include "kinematicComponent.h"
#include "shipcontrollerComponent.h"
#include "spriteComponent.h"

void Ship::Create(const Vector2D & position)
{
	TransformComponent* transformComponent = addComponent<TransformComponent>();
	transformComponent->Create(position);

	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);


	shipcontrollerComponent* shipcontroller = addComponent<shipcontrollerComponent>();
	shipcontroller->Create(600.0f);

	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\Set_000.png");


}
