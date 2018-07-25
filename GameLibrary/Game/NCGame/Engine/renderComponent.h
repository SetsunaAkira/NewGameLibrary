#pragma once

#include "components.h"

class ENGINE_API IRenderComponent : public Component
{
public:
	IRenderComponent(Entity* owner) : Component(owner) {}

	virtual void Draw() = 0;
};