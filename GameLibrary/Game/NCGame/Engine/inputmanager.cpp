#include "inputmanager.h"
#include <string.h>


bool Inputmanager::Initalize(Engine* engine)
{
	m_engine = engine;

	SDL_GetKeyboardState(&m_numKeys);
	m_KeyState = new Uint8[m_numKeys];
	m_prevKeyState = new Uint8[m_numKeys];

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_KeyState, keystate, m_numKeys);
	memcpy(m_prevKeyState, keystate, m_numKeys);

	
	
		m_mousebuttonState = SDL_GetMouseState(nullptr, nullptr);		
		m_prevmousebuttonState = m_mousebuttonState;

		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
			{
				ControllerInfo controllerinfo;
				controllerinfo.controller = SDL_GameControllerOpen(i);
				memset(controllerinfo.buttonState, 0, SDL_CONTROLLER_BUTTON_MAX);
				memset(controllerinfo.prevbuttonState, 0, SDL_CONTROLLER_BUTTON_MAX);
				memset(controllerinfo.axis, 0, SDL_CONTROLLER_AXIS_MAX);
				memset(controllerinfo.prevaxis, 0, SDL_CONTROLLER_AXIS_MAX);

				m_controllers.push_back(controllerinfo);
			}
		}
	

	return true;
}

void Inputmanager::Update()
{
	memcpy(m_prevKeyState, m_KeyState, m_numKeys);
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_KeyState, keystate, m_numKeys);

	m_prevmousebuttonState = m_mousebuttonState;
	m_mousebuttonState = SDL_GetMouseState(nullptr, nullptr);
	m_prevmousePosition = m_mousePosition;
	SDL_Point axis;
	SDL_GetMouseState(&axis.x, &axis.y);
	m_mousePosition = axis;

	for (ControllerInfo& controllerInfo : m_controllers)
	{
		memcpy(controllerInfo.prevbuttonState, controllerInfo.buttonState, SDL_CONTROLLER_BUTTON_MAX);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
		{
			controllerInfo.buttonState[i] = SDL_GameControllerGetButton(controllerInfo.controller, (SDL_GameControllerButton)i);
		}

		memcpy(controllerInfo.prevaxis, controllerInfo.axis, SDL_CONTROLLER_AXIS_MAX);
		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++)
		{
			Sint16 value = SDL_GameControllerGetAxis(controllerInfo.controller,(SDL_GameControllerAxis) i);
			controllerInfo.axis[i] = static_cast<float>(value / SDL_MAX_SINT16);
		}
	}
/*
	memcpy(m_prevbuttonState, m_buttonState, 5);
	const Uint32* buttonstate = SDL_GetMouseState(NULL,NULL);
	memcpy(m_buttontate, buttonstate, 5);*/
}


void Inputmanager::Shutdown()
{
	delete m_KeyState;
	delete m_prevKeyState;
}

void Inputmanager::AddAction(const std::string & action, int id, eDevice device, int index)
{
	auto iter = m_actions.find(action);
	if (iter == m_actions.end())
	{
		InputInfo inputinfo = { id, device, index };
		m_actions[action] = inputinfo;
	}
}

Inputmanager::ebuttonState Inputmanager::GetActionButton(const std::string & action)
{
	ebuttonState state = ebuttonState::IDLE;

	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputinfo = iter->second;
		state = GetButtonState(inputinfo.id, inputinfo.device, inputinfo.index);
	}

	return state;
}

float Inputmanager::getActionAbsolute(const std::string & action)
{
	float axis = 0.0f;

	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputinfo = iter->second;
		axis = GetAxisAbsolute(inputinfo.id, inputinfo.device, inputinfo.index);
	}

	return axis;
}

float Inputmanager::getActionRelative(const std::string & action)
{
	float axis = 0.0f;
	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputinfo = iter->second;
		axis = GetAxisRelative(inputinfo.id, inputinfo.device, inputinfo.index);
	}
	return axis;
}

float Inputmanager::GetAxisAbsolute(int id, eDevice device, int index)
{
	float axis = 0.0f;

	switch (device)
	{

	case eDevice::KEYBOARD:
		assert(0);
		break;

	case eDevice::MOUSE:
		axis = m_mousePosition[id];
		break;

	case eDevice::CONTROLLER:
		assert(index < m_controllers.size());
		axis = m_controllers[index].axis[id];
		break;
	}

	return axis;
}

float Inputmanager::GetAxisRelative(int id, eDevice device, int index)
{
	float axis = 0.0f;

	switch (device)
	{

	case eDevice::KEYBOARD:
		assert(0);
		break;

	case eDevice::MOUSE:
		axis = m_mousePosition[id] - m_prevmousePosition[id];
		break;

	case eDevice::CONTROLLER:
		assert(index < m_controllers.size());
		axis = m_controllers[index].axis[id] - m_controllers[index].prevaxis[id];
		break;
	}

	return axis;
}

Inputmanager::ebuttonState Inputmanager::GetButtonState(int id, eDevice device, int index)
{
	ebuttonState state = ebuttonState::IDLE;

	bool buttonDown = GetButtonDown(id, device, index);
	bool prevbuttonDown = GetButtonDown(id, device, index);

	if (buttonDown)
	{
		state = (prevbuttonDown) ? ebuttonState::PRESSED : ebuttonState::HELD;
	}
	else
	{
		state = (prevbuttonDown) ? ebuttonState::RELEASED : ebuttonState::IDLE;
	}

	return state;
}

bool Inputmanager::GetButtonDown(int id, eDevice device, int index)
{
	bool buttonDown = false;

	switch (device)
	{

	case eDevice::KEYBOARD:
		buttonDown = m_KeyState[id];
		break;

	case eDevice::MOUSE:
		buttonDown = m_mousebuttonState & SDL_BUTTON(id);
		break;

	case eDevice::CONTROLLER:
		assert(index < m_controllers.size());
		buttonDown = m_controllers[index].buttonState[id];
		break;
	}

	return buttonDown;
}

bool Inputmanager::GetPreviousButtonDown(int id, eDevice device, int index)
{
	bool buttonDown = false;

	switch (device)
	{

	case eDevice::KEYBOARD:
		buttonDown = m_prevKeyState[id];
		break;

	case eDevice::MOUSE:
		buttonDown = m_prevmousebuttonState & SDL_BUTTON(id);
		break;

	case eDevice::CONTROLLER:
		assert(index < m_controllers.size());
		buttonDown = m_controllers[index].prevbuttonState[id];
		break;
	}

	return buttonDown;
}
