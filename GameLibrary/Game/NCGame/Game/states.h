#pragma once
#include "state.h"
#include "stateMachine.h"
#include "color.h"
#include "timer.h"

class TitleState : public IState
{
public:
	TitleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	size_t m_credits = 0;
	Color color = Color::white;
	float m_timer = 2.0f;
	bool m_isActive = true;
};

class EnterStageState : public IState
{
public:
	EnterStageState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	size_t m_credits = 0;
	Color color = Color::white;
	float m_timer = 2.0f;
	bool m_isActive = true;
};

class GameState : public IState
{
public:
	GameState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};