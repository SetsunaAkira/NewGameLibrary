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
	std::list<Entity*>::iterator iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		if ((*iter)->GetState() == Entity::DESTROY)
		{
			iter = removeEntity(*iter);
		}
		else
		{
			iter++;
		}
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

std::list<Entity*>::iterator Scene::removeEntity(Entity * entity, bool destroy)
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

		iter = m_entities.erase(iter);
	}

	return iter;
}

Entity * Scene::GetEntityWithID(const ID & id)
{
	Entity* entity = nullptr;
	for (Entity* _entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
		}
	}
	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const ID & tag)
{
	std::vector<Entity*> entities;

	for (Entity* entity : m_entities)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}
	return entities;
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
