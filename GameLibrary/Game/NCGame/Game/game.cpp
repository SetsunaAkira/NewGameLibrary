#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "eventmanager.h"
#include "animationcomponent.h"

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	fileSystem::Instance()->setPathname("..\\content\\galaga\\");

	EventManager::Instance()->SetGameReciever(this);

	m_scene = new Scene();

	/*Entity* entity = new Entity(m_scene);
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	TextComponent* textComponent = entity->addComponent<TextComponent>();
	textComponent->Create("YEET", "namco.ttf", 40, Color::cyan);
	textComponent->SetDepth(100);
	m_scene->addEntity(entity);*/

	Entity* explosion = new Entity(m_scene);
	explosion->GetTransform().position = Vector2D(400.0f, 300.0f);
	explosion->GetTransform().scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = explosion->addComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = explosion->addComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "ship-explosion01.png", "ship-explosion02.png","ship-explosion03.png", "ship-explosion04.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f);
	m_scene->addEntity(explosion);


	Entity* score = new Entity(m_scene);
	score->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* scoreComponent = score->addComponent<TextComponent>();
	scoreComponent->Create("000000", "namco.ttf", 18, Color::white);
	scoreComponent->SetDepth(100);
	m_scene->addEntity(score);

	/*Entity* entity = new Entity(m_scene);
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spritComponent = entity->addComponent<SpriteComponent>();
	spritComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spritComponent->SetDepth(100);
	m_scene->addEntity(entity);*/

	Ship* ship = new Ship(m_scene);
	ship->Create(Vector2D(400.0f, 510.0f));
	m_scene->addEntity(ship);

	for (size_t i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(m_scene);
		float x = Math::GetRandomRange(0.0f, 600.0f);
		float y = Math::GetRandomRange(0.0f, 800.0f);
		enemy->Create(Vector2D(x, y));
		m_scene->addEntity(enemy);
	}
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

	Entity* scoreEntity = m_scene->GetEntityWithID("score");
	if (scoreEntity)
	{
		TextComponent* textComponent = scoreEntity->GetComponent<TextComponent>();
		std::string score = std::to_string(m_score);
		textComponent->SetText(score);
	}

	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	Renderer::Instance()->SetColor(Color::black);
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.EventID == "add_score")
	{
		m_score = m_score + 100000;
	}
}
