#pragma once

#include "object.h"

class Entity;

class ENGINE_API Component : public Object
{
public:
	Component(Entity* sensei, const ID& id = ID()) : m_sensei(sensei), Object(id) {}

protected:
	Entity * m_sensei = nullptr;
};
