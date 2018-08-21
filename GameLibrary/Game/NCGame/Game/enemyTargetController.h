#pragma once
#include "entity.h"
#include "controllerComponent.h"
#include "vector2D.h"

class EnemyTargetController: public IControllerComponent
{
public:
	EnemyTargetController(Entity* sensei) : IControllerComponent(sensei) {}

	void Create(const Vector2D& target,float speed);
	void Destroy();
	void Update();

protected:
	float m_speed;
	Vector2D m_target;

	float m_timer;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;
};

