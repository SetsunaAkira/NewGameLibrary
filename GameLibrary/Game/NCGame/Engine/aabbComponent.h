#pragma once
#include "collisionComponent.h"
#include "aabb.h"
#include "id.h"
class ENGINE_API AABBComponent : public ICollisionComponent
{
public:
	AABBComponent(Entity* owner) : ICollisionComponent(owner){}
	
	void Create(const ID& id,const Vector2D& offset = Vector2D::one);
	void Destroy();
	void Update();
	bool Intersects(ICollisionComponent* other);

protected:
	AABB m_aabb;
	Vector2D m_offset;
	ID m_tag;
};

