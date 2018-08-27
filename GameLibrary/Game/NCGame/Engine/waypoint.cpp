#include "waypoint.h"
#include "aabbComponent.h"

void Waypoint::Create(const Vector2D & position, const Vector2D & scale, Entity * sensei)
{
	m_sensei = sensei;
	m_transform.position = position;
	m_transform.scale = scale;

	AABBComponent* aabbcomponent = AddComponent<AABBComponent>();
	aabbcomponent->Create("waypoint",Vector2D::one);
}



void Waypoint::Update()
{
	Entity::Update();
}
