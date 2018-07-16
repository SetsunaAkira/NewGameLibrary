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

Vector2D position(0.0f, 0.0f);
float angle = 0.0f;
SDL_Texture* texture;
Text* text;

bool Engine::Initialize()
{
	/*TTF_Init();
	TTF_Quit();
	TTF_Font * font = TTF_OpenFont("..\\content\\Raleway-Black.ttf", 25);
	TTF_CloseFont(font);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font,
		"I need Healing", color);
	texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);*/
	


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


	text = Textmanager::Instance()->CreateText("STROBE LIGHTS CAUSE AIDS", "..\\content\\Raleway-Black.ttf", 24, Color::red);

	return true;
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Inputmanager::Instance()->Update();

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


	int x, y;
	SDL_GetMouseState(&x, &y);
	
	/*if (Inputmanager::Instance()->GetActionButton("LightPunch") == Inputmanager::ebuttonState::PRESSED || Inputmanager::Instance()->GetButtonState(SDL_CONTROLLER_BUTTON_A) == Inputmanager::ebuttonState::HELD)
	{
		std::cout << "YEET" << std::endl;
	}*/

	if (Inputmanager::Instance()->GetActionButton("space") == Inputmanager::ebuttonState::PRESSED)
	{
		std::cout << "YEET" << std::endl;
		Audiosystem::Instance()->PlaySound("metalhit",false);
	}

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	if (keystate[SDL_SCANCODE_LEFT]) angle -= 90.0f *Timer::Instance()->DeltaTimer();
	if (keystate[SDL_SCANCODE_RIGHT]) angle += 90.0f *Timer::Instance()->DeltaTimer();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_UP]) force.y = -200.0f * Timer::Instance()->DeltaTimer();
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTimer();

	/*Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;*/

	Renderer::Instance()->BeginFrame();

	Renderer::Instance()->SetColor(Color::black);

	
	
	////DRAW
//	SDL_Texture* Captain = TextureManager::Instance()->GetTexture("..\\Content\\Falcon.bmp");
	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);
	Renderer::Instance()->DrawTexure(texture,position, angle);
	Renderer::Instance()->EndFrame();
	



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
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Audiosystem::Instance()->Shutdown();
	Inputmanager::Instance()->Shutdown();
	//SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
