#include "states.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"
#include "audiosystem.h"

void TitleState::Enter()
{
	Entity* logo = m_sensei->GetScene()->addEntity<Entity>("logo");
	logo->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = logo->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	Audiosystem::Instance()->AddSong("Start", "Galaga.mp3");
	Audiosystem::Instance()->PlaySound("Start", true);

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
	Audiosystem::Instance()->RemoveSound("Start");
}

void GameState::Enter()
{
	std::vector<Enemy::Info> formation = 
	{
		{Enemy::BEE,Enemy::RIGHT, 350.0f, Vector2D(200.0f,100.0f)},
	    {Enemy::BEE,Enemy::LEFT, 350.0f, Vector2D(300.0f,100.0f)},
		{Enemy::BEE,Enemy::RIGHT, 350.0f, Vector2D(50.0f,100.0f)},
		{Enemy::BOSS,Enemy::LEFT, 300.0f, Vector2D(100.0f,100.0f)},
		{Enemy::BOSS,Enemy::RIGHT, 300.0f, Vector2D(250.0f,100.0f)},
		{Enemy::BOSS,Enemy::LEFT, 300.0f, Vector2D(400.0f,100.0f) },
	};

	for (Enemy::Info info : formation)
	{
		Enemy* enemy = m_sensei->GetScene()->addEntity<Enemy>();
		enemy->Create(info);
	}
	Audiosystem::Instance()->AddSong("Blood Drain", "Beat Eat Nest.mp3");
	Audiosystem::Instance()->PlaySound("Blood Drain", true);
}

void GameState::Update()
{
}

void GameState::Exit()
{
}

