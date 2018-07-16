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



bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	Timer::Instance()->Initalize(this);
	Renderer::Instance()->Initalize(this);
	TextureManager::Instance()->Initialize(this);
	Audiosystem::Instance()->Initalize(this);
	Inputmanager::Instance()->Initalize(this);
	Textmanager::Instance()->Initialize(this);

	Inputmanager::Instance()->AddAction("space", SDL_SCANCODE_SPACE, Inputmanager::eDevice::KEYBOARD);
	Audiosystem::Instance()->AddSound("metalhit", "..\\content\\Oof.mp3");
	//Inputmanager::Instance()->AddAction("LightPunch", SDL_CONTROLLER_BUTTON_A, Inputmanager::eDevice::CONTROLLER);
	//Inputmanager::Instance()->AddAction("steer", Inputmanager::eAxis::X, Inputmanager::eDevice::CONTROLLER);


	
	return true;
}

void Engine::Update()
{
	


	///*SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//SDL_RenderClear(m_renderer);*/
	//
	////DRAW
	//SDL_Rect rect = { x, y, 64, 64 };
	//SDL_Texture* Captain = TextureManager::Instance()->GetTexture("..\\Content\\Falcon.bmp");
	//assert(Captain);
	////m_texture = SDL_CreateTextureFromSurface(m_renderer, Captaon);
	//
	//SDL_QueryTexture(Captain, nullptr, nullptr, &rect.w, &rect.h);
	////SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	//SDL_RenderCopyEx(m_renderer, Captain, nullptr, &rect, 45.0f, nullptr, SDL_FLIP_NONE);

	////SDL_RenderFillRect(m_renderer, &rect);
	//SDL_RenderPresent(m_renderer);
}

void Engine::Shutdown()
{
	
}
