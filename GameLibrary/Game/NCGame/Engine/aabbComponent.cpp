#include "aabbComponent.h"
#include "transform.h"
#include "entity.h"
#include "spriteComponent.h"
#include "texture.h"
#include "debugdraw.h"

void AABBComponent::Create(const Vector2D& offset)
{
	m_offset = offset;
}

void AABBComponent::Destroy()
{
	//
}

void AABBComponent::Update()
{
	Transform transform = m_sensei->GetTransform();
	Vector2D position = transform.position;
	Vector2D size = transform.scale * m_offset;

	SpriteComponent* spriteComponent = m_sensei->GetComponent<SpriteComponent>();
	if (spriteComponent)
	{
		size = size * spriteComponent->GetTexture()->GetSize();
		position = position - (size * spriteComponent->GetOrigin());
	}
	m_aabb.Build(position, size * 0.5f);

	DEBUG_DRAW_AABB(m_aabb,Color::red);
}

bool AABBComponent::Intersects(ICollisionComponent * other)
{
	bool intersects = false;

	AABBComponent* aabbComponent = dynamic_cast<AABBComponent*>(other);
	if (aabbComponent)
	{
		intersects = m_aabb.Intersects(aabbComponent->m_aabb);
	}


	return intersects;
}
