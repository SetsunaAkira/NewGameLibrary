#pragma once
#include "object.h"
#include "components.h"
#include <vector>
#include <assert.h>
#include "scene.h"
#include "transform.h"
#include "event.h"
#include "eventreciever.h"
#include "collisionComponent.h"

class ENGINE_API Entity : public Object, public EventReciever
{
public:
	enum eState
	{
		INACTIVE,
		ACTIVE,
		DESTROY
	};



public:
	Entity(Scene* scene, const ID& id = ID()) :m_scene(scene), Object(id) {}
	virtual ~Entity() {}

	virtual void Destroy();
	virtual void Update();
	virtual void Draw();

	virtual void OnEvent(const Event& event);

	template <typename T>
	T* addComponent()
	{
		T* component = new T(this);
		assert(dynamic_cast<Component*>(component));
		m_components.push_back(component);

		return component;
	}

	bool Intersects(Entity* otherEntity)
	{
		bool intersects = false;
		ICollisionComponent* collisionA = GetComponent<ICollisionComponent>();
		ICollisionComponent* collisionB = otherEntity->GetComponent<ICollisionComponent>();

		if (collisionA && collisionB)
		{
			intersects = collisionA->Intersects(collisionB);
		}

		return intersects;
	}

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

	eState GetState() { return m_state; }
	eState SetState(eState state) { return m_state = state; }

	Scene* Getscene() { return m_scene; }
	Transform & GetTransform() 
	{ 
		return m_transform; 
	}

	void SetTag(const ID& tag) { m_tag = tag; }
	const ID& GetTag() { return m_tag; }

protected:
	eState m_state = eState::ACTIVE;
	ID m_tag;
	Transform  m_transform;
	Scene * m_scene;
	std::vector<Component*> m_components;
};