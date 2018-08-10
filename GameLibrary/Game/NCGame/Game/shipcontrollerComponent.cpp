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

	Audiosystem::Instance()->AddSound("pew", "laser.wav");
	std::cout << "actions" << std::endl;
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
		//kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}

	if (Inputmanager::Instance()->GetActionButton("fire") == Inputmanager::ebuttonState::PRESSED)
	{
		Missile* missile = new Missile(m_sensei->Getscene());
		missile->Create("playermissile",m_sensei->GetTransform().position, Vector2D::down, 800.0f);
		m_sensei->Getscene()->addEntity(missile);
		Audiosystem::Instance()->PlaySound("pew",false);
	}

}
