#pragma once
#include "engine.h"

class StateMachine;
class ENGINE_API IState
{
public:
	IState(StateMachine* owner) : m_sensei(owner){}
	virtual ~IState(){}

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

protected:
	StateMachine * m_sensei = nullptr;
};
