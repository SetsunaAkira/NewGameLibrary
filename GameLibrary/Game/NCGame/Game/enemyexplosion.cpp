#include "enemyexplosion.h"
#include "spriteComponent.h"
#include "animationcomponent.h"
#include "audiosystem.h"

void EnemyExplosion::Create(const Vector2D & postion)
{
	postion;
	m_transform.position = Vector2D(400.0f, 300.0f);
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = addComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "enemy-explosion01.png", "enemy-explosion02.png","enemy-explosion03.png", "enemy-explosion04.png", "enemy-explosion05.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME);
	
	Audiosystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
	Audiosystem::Instance()->PlaySound("explosion", false);

}

void EnemyExplosion::Update()
{
}
