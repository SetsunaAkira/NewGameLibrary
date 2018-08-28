#pragma once
#include "singleton.h"
#include "engine.h"

class ENGINE_API Timer : public Singleton<Timer>
{
public:
	bool Initalize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTimer() const { return m_dt * m_timeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	void setTimeScale(float timescale) { m_timeScale = timescale; }
	float GetTimeScale() const { return m_timeScale; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }
	bool isPaused() { return m_paused; }

	void Reset();

	friend Singleton<Timer>;

protected:
	Timer() {}

private:
	Engine * m_engine;
	float m_fps; //
	float m_dt;
	float m_timeScale;
	int m_frameCounter; //
	Uint32 m_prevTicks;
	Uint32 m_startTicks; //
	bool m_paused;
	const int FRAME_COUNT = 100;
};

