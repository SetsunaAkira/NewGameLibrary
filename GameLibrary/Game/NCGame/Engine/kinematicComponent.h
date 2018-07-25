#pragma once
#include "physicsComponent.h"

class kinematicComponent : public IPhysicsComponent
{
public:
	kinematicComponent(Entity* owner) : IPhysicsComponent(owner) {}

	void Create(float velocityMax, float dampening = 1.0f, bool enableGravity = false);
	void Destroy();

	void SetVelocity(const Vector2D& force, eForceType forcetype) { m_velocity = m_velocity; }
	const Vector2D& GetVelocity() const { return m_velocity; }
	void SetVelocityMax(float velocityMax) { m_velocityMax = velocityMax; }

	void ApplyForce(const Vector2D& force, eForceType forceType);
	void Enablegravity(bool enableGravity = true) { m_enableGravity = enableGravity; }

protected:
	bool m_enableGravity = false;
	float m_dampening = 1.0f;

	eForceType m_forcetype;
	Vector2D m_velocity;
	float m_velocityMax;
	Vector2D m_force;

};

