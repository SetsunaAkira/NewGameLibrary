#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "enemyWaypointControllerComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "enemyexplosion.h"

void Enemy::Create(const Vector2D & position)
{
	SetTag("enemy");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	kinematicComponent* kinematic = addComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	/*enemycontrollerComponent* controller = addComponent<enemycontrollerComponent>();
	controller->Create(200.0f);*/

	EnemyWaypointControllerComponent* controller = addComponent<EnemyWaypointControllerComponent>();
	std::vector<Vector2D> points = { Vector2D(100.0f, 100.0f), Vector2D(300.0f,400.0f), Vector2D(96.0f, -400.0f) };
	controller->Create(200.0f, points);


	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = addComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

	Audiosystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
}

void Enemy::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y + 64.0f)
	{
		float x = Math::GetRandomRange(0.0f, size.x);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}
}

void Enemy::OnEvent(const Event & event)
{
	if (event.EventID == "collision")
	{
		if (event.sender->GetTag() == "playermissle")
		{
			Event _event;
			_event.EventID = "add_score";
			EventManager::Instance()->SendGameMessage(_event);
			m_scene->addEntity<EnemyExplosion>();
			EnemyExplosion *explosion = m_scene->addEntity<EnemyExplosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
			Audiosystem::Instance()->PlaySound("explosion",false);
		}
	}
}
