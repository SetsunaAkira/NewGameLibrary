#pragma once
#include "engine.h"
#include <map>

class Entity;
class IState;
class Scene;
class ENGINE_API StateMachine
{
public:
	StateMachine(Scene* scene, Entity* entity = nullptr) : m_scene(scene), m_sensei(entity){}
	~StateMachine() {}

	void Update();
	void AddState(const std::string& stateName, IState* state);
	void SetState(const std::string& stateName);
	Scene* GetScene() { return m_scene; }
	Entity* GetEntity() { return m_sensei; }

	template<typename T>
	T* GetEntity()
	{
		return dynamic_cast<T*> (m_sensei);
	}

protected:
	Scene * m_scene = nullptr;
	IState* m_state = nullptr;
	Entity* m_sensei = nullptr;
	std::map<std::string, IState*> m_states;
};

