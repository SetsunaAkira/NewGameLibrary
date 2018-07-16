#include "timer.h"


bool Timer::Initalize(Engine * engine)
{
	m_paused = false;
	m_TimeScale = 1.0f;
	m_engine = engine;
	return true;
}

void Timer::Shutdown()
{

}

void Timer::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 milleseconds = ticks - m_prevTicks;
	m_prevTicks = ticks;

	m_dt = (m_paused) ? 0.0f : milleseconds / 1000.0f;
}
