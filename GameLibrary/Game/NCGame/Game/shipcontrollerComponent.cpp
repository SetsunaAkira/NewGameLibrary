#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "inputManager.h"
#include "audioSystem.h"
#include "entity.h"
#include "missile.h"
#include <iostream>

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	Inputmanager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, Inputmanager::eDevice::KEYBOARD);
	Inputmanager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, Inputmanager::eDevice::KEYBOARD);
	Inputmanager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, Inputmanager::eDevice::KEYBOARD);

	Audiosystem::Instance()->AddSound("fire", "laser.wav");
}

void ShipControllerComponent::Destroy()
{
}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if ((Inputmanager::Instance()->GetActionButton("left") == Inputmanager::ebuttonState::PRESSED) ||
		(Inputmanager::Instance()->GetActionButton("left") == Inputmanager::ebuttonState::HELD))
	{
		force = force + Vector2D::left;
	}

	if ((Inputmanager::Instance()->GetActionButton("right") == Inputmanager::ebuttonState::PRESSED) ||
		(Inputmanager::Instance()->GetActionButton("right") == Inputmanager::ebuttonState::HELD))
	{
		force = force + Vector2D::right;
	}

	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}

	if (Inputmanager::Instance()->GetActionButton("fire") == Inputmanager::ebuttonState::PRESSED)
	{
		std::vector<Entity*> missiles = m_sensei->Getscene()->GetEntitiesWithTag("playermissile");
		if (missiles.size() < 4)
		{
			Missile* missile = new Missile(m_sensei->Getscene());
			missile->Create("playermissile", m_sensei->GetTransform().position, Vector2D::down, 2500.0f);
			m_sensei->Getscene()->AddEntity(missile);

			Audiosystem::Instance()->PlaySound("fire", false);
		}
	}

}
