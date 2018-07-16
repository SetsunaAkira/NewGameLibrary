#pragma once
#include "singleton.h"
#include "engine.h"
#include <vector>
#include <map>
#include "vector2D.h"

class ENGINE_API Inputmanager : public Singleton<Inputmanager>
{
public:
	enum ebuttonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDevice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y
	};

	struct InputInfo
	{
		int id;
		eDevice device;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController* controller;
		Uint8 buttonState[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 prevbuttonState[SDL_CONTROLLER_BUTTON_MAX];
		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prevaxis[SDL_CONTROLLER_AXIS_MAX];
	};

public:
	Inputmanager() {}

	bool Initalize(Engine* engine);
	void Update();
	void Shutdown();

	void AddAction(const std::string& action, int id, eDevice device, int index = 0);
	ebuttonState GetActionButton(const std::string& action);
	float getActionAbsolute(const std::string& action);
	float getActionRelative(const std::string& action);

	ebuttonState GetButtonState(int id, eDevice device = eDevice::KEYBOARD, int index = 0);
	float GetAxisAbsolute(int id, eDevice device = eDevice::CONTROLLER, int index = 0);
	float GetAxisRelative(int id, eDevice device = eDevice::CONTROLLER, int index = 0);

	

protected:
	bool GetButtonDown(int id, eDevice device, int index = 0);
	bool GetPreviousButtonDown(int id, eDevice device, int index = 0);


private:
	Engine * m_engine;
	Uint8 *m_prevKeyState;
	Uint8 *m_KeyState;

	Uint8 m_mousebuttonState;
	Uint8 m_prevmousebuttonState;
	Vector2D m_mousePosition;
	Vector2D m_prevmousePosition;

	std::vector<ControllerInfo> m_controllers;

	std::map<std::string, InputInfo> m_actions;


	int m_numKeys;
};

