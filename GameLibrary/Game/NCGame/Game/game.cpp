#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "textComponent.h"
#include "eventManager.h"
#include "statemachine.h"
#include "states.h"

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	fileSystem::Instance()->setPathname("..\\Content\\Galaga\\");

	EventManager::Instance()->SetGameReciever(this);

	m_scene = new Scene();

	m_statemachine = new StateMachine(m_scene);

	m_statemachine->AddState("title", new TitleState(m_statemachine));
	m_statemachine->AddState("enter_stage", new EnterStageState(m_statemachine));
	m_statemachine->AddState("game", new GameState(m_statemachine));
	m_statemachine->SetState("title");

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = entity->AddComponent<TextComponent>();
	textComponent->Create("00000", "emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(100);
	m_scene->AddEntity(entity);

	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400, 510));
	m_scene->AddEntity(ship);

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
		while (score.length() < 5) score = "0" + score;
		textComponent->SetText(score);
	}

	m_statemachine->Update();

	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.EventID == "add_score")
	{
		m_score = m_score + 100;
	}
}

