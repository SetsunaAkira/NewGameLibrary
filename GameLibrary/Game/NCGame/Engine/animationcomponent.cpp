#include "animationcomponent.h"
#include "texture.h"
#include "timer.h"
#include "spriteComponent.h"
#include "entity.h"

void AnimationComponent::Create(const std::vector<std::string>& texturenames, float rate)
{
	for (std::string texturename : texturenames)
	{
		Texture* texture = new Texture();
		texture->Create(texturename);

		m_textures.push_back(texture);
	}
	m_rate = rate;
}

void AnimationComponent::Destroy()
{
	for(Texture* texture : m_textures)
	{
		texture->Destroy();
		delete texture;
	}
	m_textures.clear();
}

void AnimationComponent::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTimer();
	if (m_timer >= m_rate)
	{
		m_timer = m_timer - m_rate;
		m_frame++;
		if (m_frame >= m_textures.size())
		{
			m_frame = 0;
		}
	}

	SpriteComponent* spriteComponent = m_sensei->GetComponent<SpriteComponent>();
	if (spriteComponent)
	{
		spriteComponent->SetTexture(GetTexture());
	}
}

Texture * AnimationComponent::GetTexture()
{
	return m_textures[m_frame];
}
