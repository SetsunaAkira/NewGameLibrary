#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include "engine.h"

class ENGINE_API TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* sensei) : IControllerComponent(sensei) {}

	void Create(const Vector2D& position,float rotation, float speed, float rotaterate);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	Vector2D m_target;
	Vector2D m_position;
	float m_rotation;
	float m_rotateRate = 0.0f;

	float m_timer;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;
};

