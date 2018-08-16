#include "states.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"

void TitleState::Enter()
{
	Entity* logo = m_sensei->GetScene()->addEntity<Entity>("logo");
	logo->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = logo->addComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	Inputmanager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, Inputmanager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	if (Inputmanager::Instance()->GetActionButton("start") == Inputmanager::ebuttonState::PRESSED)
	{
		m_sensei->SetState("game");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_sensei->GetScene()->GetEntityWithID("logo");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}

void GameState::Enter()
{
	for (size_t i = 0; i < 25; i++)
	{
		Enemy* enemy = new Enemy(m_sensei->GetScene());
		float x = Math::GetRandomRange(0.0f, 800.0f);
		float y = Math::GetRandomRange(-30.0f, -300.0f);
		enemy->Create(Vector2D(x, y));
		m_sensei->GetScene()->addEntity(enemy);
	}
}

void GameState::Update()
{
}

void GameState::Exit()
{
}

