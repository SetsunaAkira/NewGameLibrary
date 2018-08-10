#include "engine.h"
#include <cassert>
#include "textureManager.h"
#include "renderer.h"
#include "audiosystem.h"
#include "inputmanager.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include <iostream>
#include "SDL_ttf.h"
#include "text.h"
#include "textmanager.h"
#include "audiosystem.h"
#include "physics.h"
#include "fileSystem.h"



bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	fileSystem::Instance()->Initialize(this);
	Timer::Instance()->Initalize(this);
	Renderer::Instance()->Initalize(this);
	TextureManager::Instance()->Initialize(this);
	Audiosystem::Instance()->Initalize(this);
	Inputmanager::Instance()->Initalize(this);
	Textmanager::Instance()->Initialize(this);
	Physics::Instance()->Initialize(this);	
	return true;
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->Update();
	Inputmanager::Instance()->Update();
	Audiosystem::Instance()->Update();
	Physics::Instance()->Update();
	fileSystem::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}

	SDL_PumpEvents();
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Audiosystem::Instance()->Shutdown();
	Inputmanager::Instance()->Shutdown();
	Textmanager::Instance()->Shutdown();
	Physics::Instance()->Shutdown();
	fileSystem::Instance()->Shutdown();
}
