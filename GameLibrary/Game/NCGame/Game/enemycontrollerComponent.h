#pragma once
#include "entity.h"
#include "controllerComponent.h"
class enemycontrollerComponent : public IControllerComponent
{
public:
	enemycontrollerComponent(Entity* sensei) : IControllerComponent(sensei) {}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed;
};

