#include "states.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"
#include "audiosystem.h"
#include "textComponent.h"
#include "formation.h"
#include "timer.h"

void TitleState::Enter()
{
	Entity* logo = m_sensei->GetScene()->AddEntity<Entity>("logo");
	logo->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = logo->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	Entity* start = m_sensei->GetScene()->AddEntity<Entity>("start");
	start->GetTransform().position = Vector2D(290, 450);
	TextComponent* textComponent = start->AddComponent<TextComponent>();
	textComponent->Create("Press Enter to Start", "emulogic.ttf", 10, color);
	textComponent->SetDepth(100);

	Audiosystem::Instance()->AddSong("Start", "Galaga.mp3");
	Audiosystem::Instance()->PlaySound("Start", true);

	Inputmanager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, Inputmanager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	m_timer = m_timer - Timer::Instance()->DeltaTimer();
	if (m_isActive)
	{
		color.r = Math::Lerp(color.r, Color::black.r, 0.01f);
		color.b = Math::Lerp(color.b, Color::black.b, 0.01f);
		color.g = Math::Lerp(color.g, Color::black.g, 0.01f);
		if (m_timer < 0.0f)
		{
			m_isActive = false;
			m_timer = 1.5f;
		}
	}
	else if (!m_isActive)
	{
		color.r = Math::Lerp(color.r, Color::white.r, 0.01f);
		color.b = Math::Lerp(color.b, Color::white.b, 0.01f);
		color.g = Math::Lerp(color.g, Color::white.g, 0.01f);
		if (m_timer < 0.0f)
		{
			m_isActive = true;
			m_timer = 1.2f;

		}
	}


	Entity* text = m_sensei->GetScene()->GetEntityWithID("start");
	text->GetComponent<TextComponent>()->SetColor(color);

	if (Inputmanager::Instance()->GetActionButton("start") == Inputmanager::ebuttonState::PRESSED)
	{
		m_sensei->SetState("enter_stage");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_sensei->GetScene()->GetEntityWithID("logo");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
	Entity* entityStart = m_sensei->GetScene()->GetEntityWithID("start");
	if (entityStart)
	{
		entityStart->SetState(Entity::DESTROY);
	}
	Audiosystem::Instance()->RemoveSound("Start");

	
}

void GameState::Enter()
{
	
}

void GameState::Update()
{
}

void GameState::Exit()
{
}

void EnterStageState::Enter()
{
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_sensei->GetScene()->GetEntityWithID("formation"));
	if (formation == nullptr)
	{
		formation = m_sensei->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}
}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_sensei->GetScene()->GetEntityWithID("formation"));
	formation->Update();
}

void EnterStageState::Exit()
{
}
