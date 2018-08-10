#pragma once
#include "engine.h"
#include "event.h"
class ENGINE_API EventReciever
{
public:
	EventReciever(){}

	virtual void OnEvent(const Event& event) = 0;
};
