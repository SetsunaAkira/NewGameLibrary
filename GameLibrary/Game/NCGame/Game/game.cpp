#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	fileSystem::Instance()->setPathname("..\\content\\galaga\\");

	m_scene = new Scene();

	Ship* ship = new Ship(m_scene);
	ship->Create(Vector2D(400.0f, 510.0f));
	m_scene->addEntity(ship);

	Enemy* enemy = new Enemy(m_scene);
	enemy->Create(Vector2D(400.0f, 60.0f));
	m_scene->addEntity(enemy);

	m_running = success;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();

	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	Renderer::Instance()->SetColor(Color::black);
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}
