#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include <iostream>
#include "text.h"
#include "entity.h"
#include "scene.h"
#include "ship.h"
#include "textmanager.h"
#include "audiosystem.h"
#include "textureManager.h"
#include "inputmanager.h"
#include "fileSystem.h"


Vector2D position(0.0f, 0.0f);
float angle = 0.0f;
SDL_Texture* texture;
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	fileSystem::Instance()->setPathname("..\\Content\\Galaga\\");
	{
		m_scene = new Scene();
		Ship* ship = new Ship(m_scene);
		ship->Create(Vector2D(50.0f, 50.0f));
		m_scene->addEntity(ship);
	}

	m_running = success;
	return success;
}

void Game::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Audiosystem::Instance()->Shutdown();
	Inputmanager::Instance()->Shutdown();
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	m_engine->Shutdown();
}

void Game::Update()
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

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	if (keystate[SDL_SCANCODE_LEFT]) angle -= 90.0f *Timer::Instance()->DeltaTimer();
	if (keystate[SDL_SCANCODE_RIGHT]) angle += 90.0f *Timer::Instance()->DeltaTimer();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_UP]) force.y = -200.0f * Timer::Instance()->DeltaTimer();
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTimer();

	Renderer::Instance()->SetColor(Color::red);

	Renderer::Instance()->BeginFrame();

	
	m_scene->Draw();
	m_scene->Update();

	Renderer::Instance()->EndFrame();

	

	////DRAW
	//	SDL_Texture* Captain = TextureManager::Instance()->GetTexture("..\\Content\\Falcon.bmp");
	//entity->Draw();
	/*std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);*/
	//Renderer::Instance()->DrawTexure(texture, position, angle);
	
	
	m_running = !m_engine->IsQuit();
	m_engine->Update();
}
