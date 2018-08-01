#pragma once
#include "entity.h"
#include "controllerComponent.h"

class shipcontrollerComponent : public IControllerComponent
{
public:
	shipcontrollerComponent(Entity* sensei) : IControllerComponent(sensei){}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed;
};

