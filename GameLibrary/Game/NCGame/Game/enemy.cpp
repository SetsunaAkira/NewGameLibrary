#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "WaypointControllerComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "explosion.h"
#include "transformcontrollercomponent.h"
#include "timer.h"
#include "animationcomponent.h"

std::vector<Vector2D> Enemy::m_enterPath = 
{ 
	Vector2D(200.0f, 400.0f), 
	Vector2D(300.0f, 300.0f), 
	Vector2D(200.0f, 200.0f), 
	Vector2D(100.0f, 300.0f), 
	Vector2D(200.0f, 400.0f) 
};

void Enemy::Create(const Info& info)
{
	m_info = info;

	SetTag("enemy");
	m_transform.position = (m_info.side == LEFT) ? Vector2D(-64.0f, 400.0f) : Vector2D(864.0f, 400.0f);
	m_transform.scale = Vector2D(2.0f, 2.0f);

	kinematicComponent* kinematic = AddComponent<kinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();

	std::vector<std::string> animations;
	if (m_info.type == BEE) animations = { "enemy02A.png", "enemy02B.png" };
	if (m_info.type == BOSS) animations = { "enemy01A.png", "enemy01B.png" };
	animationComponent->Create(animations, 1.0f / 4.0f);


	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create("enemy",Vector2D(0.7f, 0.9f));

	Audiosystem::Instance()->AddSound("explosion", "enemy-hit01.wav");

	m_stateMachine = new StateMachine(Getscene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("enter_path");
	
}

void Enemy::Update()
{
	Entity::Update();
	m_stateMachine->Update();
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
			m_scene->addEntity<Explosion>();
			Explosion *explosion = m_scene->addEntity<Explosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
			Audiosystem::Instance()->PlaySound("explosion",false);
		}
	}
}

void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_sensei->GetEntity<Enemy>()->m_info.speed, Enemy::m_enterPath);
}
void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->isComplete())
	{
		m_sensei->GetEntity()->removeComponent(waypointController);
		m_sensei->SetState("enter_formation");
	}
}
void EnterPathState::Exit()
{

}

void EnterFormationState::Enter()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_sensei->GetEntity<Enemy>()->m_info.speed, std::vector<Vector2D> { m_sensei->GetEntity<Enemy>()->m_info.Target });
}
void EnterFormationState::Update()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->isComplete())
	{
		m_sensei->GetEntity()->removeComponent(waypointController);
		m_sensei->SetState("idle");
	}
}
void EnterFormationState::Exit()
{

}

void IdleState::Enter()
{
	TransformControllerComponent* controller = m_sensei->GetEntity()->AddComponent<TransformControllerComponent>();
	controller->Create(m_sensei->GetEntity<Enemy>()->m_info.Target, 180.0f, m_sensei->GetEntity<Enemy>()->m_info.speed, 5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTimer();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		TransformControllerComponent* controller = m_sensei->GetEntity()->AddComponent<TransformControllerComponent>();
		m_sensei->GetEntity()->removeComponent(controller);
		m_sensei->SetState("attack");
	}
}

void IdleState::Exit()
{
}

void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_sensei->GetEntity<Enemy>()->m_info.speed, Enemy::m_enterPath);
}

void AttackState::Update()
{
	WaypointControllerComponent* waypointController = m_sensei->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->isComplete())
	{
		m_sensei->GetEntity()->removeComponent(waypointController);
		m_sensei->SetState("enter_formation");
	}
}

void AttackState::Exit()
{
	m_sensei->GetEntity()->GetTransform().position.y = -64.0f;
}
