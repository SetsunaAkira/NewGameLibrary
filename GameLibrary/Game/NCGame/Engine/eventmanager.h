#pragma once
#include "singleton.h"
#include "engine.h"
#include "event.h"
#include "eventreciever.h"
class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	EventManager(){}
	
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);
	void SendGameMessage(const Event& event);

	void SetGameReciever(EventReciever* eventreciever) { m_gamereciever = eventreciever; }
protected:
	friend Singleton<EventManager>;

protected:
	Engine * m_engine;
	EventReciever* m_gamereciever = nullptr;

};

