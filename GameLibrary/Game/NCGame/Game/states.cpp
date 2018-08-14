#include "states.h"
#include "spriteComponent.h"
#include "statemachine.h"
#include "entity.h"
#include "inputmanager.h"
#include "scene.h"

void TitleState::Enter()
{
	Entity* entity = m_sensei->GetScene()->addEntity<Entity>();
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->addComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	Inputmanager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, Inputmanager::eDevice::KEYBOARD);
}

void TitleState::Update()
{

}

void TitleState::Exit()
{

}
