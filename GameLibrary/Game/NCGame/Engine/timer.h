#pragma once
#include "singleton.h"
#include "engine.h"

class ENGINE_API Timer : public Singleton<Timer>
{
public:
	bool Initalize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTimer() const { return m_dt * m_TimeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	void setTimeScale(float timescale) { m_TimeScale = timescale; }
	float GetTimeScale() const { return m_TimeScale; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }
	bool isPaused() { return m_paused; }

	friend Singleton<Timer>;

protected:
	Timer() {}

private:
	Engine * m_engine;
	float m_dt;
	Uint32 m_prevTicks;
	bool m_paused;
	float m_TimeScale;

};

