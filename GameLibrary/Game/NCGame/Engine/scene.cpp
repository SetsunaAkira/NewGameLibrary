#include "scene.h"
#include "entity.h"
#include <assert.h>
#include "id.h"


bool Scene::Intialize()
{
	return false;
}

void Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::addEntity(Entity * entity)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());
	assert(entity);
	m_entities.push_back(entity);
}

void Scene::removeEntity(Entity * entity, bool destroy)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());
	assert(entity);

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		if (destroy)
		{
			(*iter)->Destroy();
			delete *iter;
		}
		m_entities.erase(iter);
	}
}

void Scene::Draw()
{
	for (Entity* entity : m_entities)
	{
		entity->Draw();
	}
}

Entity * Scene::findEntity(const ID & id)
{
	Entity* _entity = nullptr;
	for (Entity* entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
			break;
		}
	}
	return _entity;
}
