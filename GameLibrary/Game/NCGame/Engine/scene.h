#pragma once
#include <vector>
#include "id.h"
#include "engine.h"

class Entity;

class ENGINE_API Scene
{
public:
	Scene(){}
	~Scene(){}

	bool Intialize();
	void Update();
	void Shutdown();

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void Draw();

	Entity* findEntity(const ID& id);



protected:
	std::vector<Entity*> m_entities;

};

