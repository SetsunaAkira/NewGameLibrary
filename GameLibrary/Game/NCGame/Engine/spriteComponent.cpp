#include "spriteComponent.h"
#include "texture.h"
#include "entity.h"
#include "renderer.h"
#include <iostream>
void SpriteComponent::Create(const std::string & textureName, const Vector2D& origin)
{
	if (textureName != "")
	{
		m_texture = new Texture();
		m_texture->Create(textureName);
	}
	m_origin = origin;
	std::cout << "Create" << std::endl;
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{
	if (m_texture)
	{
		Transform transform = m_sensei->GetTransform();
		m_texture->Draw(transform.position, m_origin, transform.scale, transform.rotation);
	}
}
