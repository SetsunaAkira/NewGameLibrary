#pragma once
#include "id.h"

class Entity;

struct Event
{
	ID EventID;
	Entity* sender;
	Entity* reciever;

	Event(){}
};
