#include "shipcontrollerComponent.h"
#include "inputmanager.h"
#include "audiosystem.h"

void shipcontrollerComponent::Create(float speed)
{
	m_speed = speed;

	Inputmanager::Instance()->AddAction("space", SDL_SCANCODE_SPACE, Inputmanager::eDevice::KEYBOARD);
	Audiosystem::Instance()->AddSound("metalhit", "..\\content\\Oof.mp3");
}

void shipcontrollerComponent::Destroy()
{
}

void shipcontrollerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if ((Inputmanager::Instance()->GetActionButton("left") == Inputmanager::ebuttonState::PRESSED) ||
		(Inputmanager::Instance()->GetActionButton("left") == Inputmanager::ebuttonState::HELD))
	{
		// force x <- -1.0
	}

	if ((Inputmanager::Instance()->GetActionButton("right") == Inputmanager::ebuttonState::PRESSED) ||
		(Inputmanager::Instance()->GetActionButton("right") == Inputmanager::ebuttonState::HELD))
	{
		// force x -> 1.0
	}

	// get transform component
	// tranform position = transform position + force * speed

	if (Inputmanager::Instance()->GetActionButton("space") == Inputmanager::ebuttonState::PRESSED)
	{
		Audiosystem::Instance()->PlaySound("metalhit", false);
	}
}
