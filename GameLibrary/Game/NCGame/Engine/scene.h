#pragma once
#include <vector>
#include "id.h"
#include "engine.h"
#include <list>

class Entity;

class ENGINE_API Scene
{
public:
	Scene(){}
	~Scene(){}

	bool Intialize();
	void Update();
	void Shutdown();
	void Draw();

	void addEntity(Entity* entity);
	std::list<Entity*>::iterator removeEntity(Entity* entity, bool destroy = true);

	Entity* GetEntityWithID(const ID& id);
	std::vector<Entity*> GetEntitiesWithTag(const ID& tag);
	

	Entity* findEntity(const ID& id);



protected:
	std::list<Entity*> m_entities;
	
};

