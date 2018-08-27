#pragma once

#include "object.h"

class Entity;

class ENGINE_API Component : public Object
{
public:
	Component(Entity* sensei, const ID& id = ID()) : m_sensei(sensei), Object(id) {}
	
	virtual void Destroy() = 0;
	virtual void Update() = 0;

	Entity* GetOwner() { return m_sensei; }
protected:
	Entity * m_sensei = nullptr;
};
