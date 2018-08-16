#pragma once
#include "engine.h"
#include "entity.h"


class ENGINE_API Waypoint : public Entity
{
public:
	Waypoint(Scene* scene, const ID& id) : Entity(scene, id){}

	void Create(const Vector2D& position, const Vector2D& scale, Entity* sensei);
	void Update();

protected:
	Entity * m_sensei = nullptr;
};
