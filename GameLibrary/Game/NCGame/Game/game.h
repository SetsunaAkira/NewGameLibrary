#pragma once

#include "SDL.h"

class Engine;

class Game
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}
	
	bool Initialize();
	void Shutdown();
	void Update();
	bool Run(){ return m_running; }

protected:
	bool m_running = false;
	Engine* m_engine;
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
};

