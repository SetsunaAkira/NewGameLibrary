#include "entity.h"
#include <assert.h>
#include "renderComponent.h"

void Entity::Destroy()
{
	for (Component* component : m_components)
	{
		component->Destroy();
		delete component;
	}

	m_components.clear();
}
void Entity::Update()
{
	for (Component* component : m_components)
	{
		component->Update();
	}

}

void Entity::Draw()
{
	IRenderComponent* renderComponent = GetComponent<IRenderComponent>();
	if (renderComponent)
	{
		renderComponent->Draw();
	}
}

void Entity::OnEvent(const Event & event)
{
	event;
}

void Entity::AddComponent(Component * component)
{
	assert(component);
	assert(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	m_components.push_back(component);
}

void Entity::removeComponent(Component * component)
{
	assert(std::find(m_components.begin(), m_components.end(), component) != m_components.end());
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	(*iter)->Destroy();
	delete *iter;
	m_components.erase(iter);
}
