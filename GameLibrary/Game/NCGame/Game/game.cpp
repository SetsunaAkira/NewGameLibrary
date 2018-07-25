#include "game.h"
#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "audiosystem.h"
#include "inputmanager.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include <iostream>
#include "text.h"
#include "textmanager.h"
#include "audiosystem.h"
#include "entity.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "scene.h"

Vector2D position(0.0f, 0.0f);
float angle = 0.0f;
SDL_Texture* texture;
Text* text;

bool Game::Initialize()
{
	m_scene = new Scene();
	text = Textmanager::Instance()->CreateText("STROBE LIGHTS CAUSE AIDS", "..\\content\\Raleway-Black.ttf", 24, Color::red);

	for (size_t i = 0; i < 20; i++)
	{
		Entity* entity = new Entity(ID("player"));
		TransformComponent* transformComponent = new TransformComponent(entity);
		float x = (float)(rand() % 800);
		float y = (float)(rand() % 600);
		transformComponent->Create(Vector2D(x,y));
		entity->addComponent(transformComponent);

		SpriteComponent* spriteComponent = new SpriteComponent(entity);
		spriteComponent->Create("..\\content\\car.bmp");
		entity->addComponent(spriteComponent);

		m_scene->addEntity(entity);
		
	}

	bool success = m_engine->Initialize();
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
	//SDL_DestroyRenderer(m_renderer);
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


	int x, y;
	SDL_GetMouseState(&x, &y);


	

	m_scene->Update();

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

	m_scene->Draw();

	Renderer::Instance()->EndFrame();

	////DRAW
	//	SDL_Texture* Captain = TextureManager::Instance()->GetTexture("..\\Content\\Falcon.bmp");
	//entity->Draw();
	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);
	Renderer::Instance()->DrawTexure(texture, position, angle);
	
	m_running = !m_engine->IsQuit();
	m_engine->Update();
}
