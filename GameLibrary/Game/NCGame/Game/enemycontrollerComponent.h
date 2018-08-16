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
	float m_timer;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;
};

