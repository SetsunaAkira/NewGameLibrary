#pragma once
#include "object.h"
#include "components.h"
#include <vector>

class ENGINE_API Entity : public Object
{
public:
	Entity(const ID& id = ID()) : Object(id) {}
	virtual ~Entity() {}

	void Update();
	void Draw();

	void addComponent(Component* component);
	void removeComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

protected:
	std::vector<Component*> m_components;
};