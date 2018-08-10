#include "collisionComponent.h"
#include "scene.h"
#include "entity.h"
#include <vector>
#include <assert.h>
#include "id.h"
#include "event.h"
#include "eventmanager.h"
#include "renderComponent.h"
#include <algorithm>



bool Scene::Intialize()
{
	return false;
}

void Scene::Update()
{
	size_t size = m_entities.size();
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}

    std::vector<ICollisionComponent*> collisionComponents;
	for (Entity* entity : m_entities)
	{
		ICollisionComponent* collisionComponent = entity->GetComponent<ICollisionComponent>();
		if (collisionComponent)
		{
			collisionComponents.push_back(collisionComponent);
		}
	}

	for (size_t i = 0; i < collisionComponents.size(); i++)
	{
		for (size_t j = i + 1; j < collisionComponents.size(); j++)
		{
			if (collisionComponents[i]->Intersects(collisionComponents[j]))
			{
				Event event;
				event.EventID = "collision";
				event.reciever = collisionComponents[i]->GetOwner();
				event.sender = collisionComponents[j]->GetOwner();
				EventManager::Instance()->SendMessage(event);

				event.reciever = collisionComponents[j]->GetOwner();
				event.sender = collisionComponents[i]->GetOwner();
				EventManager::Instance()->SendMessage(event);	
			}
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
	std::vector<IRenderComponent*> renderComponents;
	for (Entity* entity : m_entities)
	{
		IRenderComponent* renderComponent = entity->GetComponent<IRenderComponent>();
		if (renderComponent)
		{
			renderComponents.push_back(renderComponent);
		}
	}

	std::sort(renderComponents.begin(), renderComponents.end(),IRenderComponent::CompareDepth);
	for (IRenderComponent* renderComponent : renderComponents)
	{
		if (renderComponent->IsVisible())
		{
			renderComponent->Draw();
		}
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
