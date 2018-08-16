#include "animationcomponent.h"
#include "texture.h"
#include "timer.h"
#include "spriteComponent.h"
#include "entity.h"

void AnimationComponent::Create(const std::vector<std::string>& texturenames, float rate, ePlayback playback)
{
	for (std::string texturename : texturenames)
	{
		Texture* texture = new Texture();
		texture->Create(texturename);

		m_textures.push_back(texture);
	}
	m_rate = rate;
	m_playback = playback;
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
		m_frame = m_frame + m_direction;
		if (m_frame >= m_textures.size())
		{
			switch (m_playback)
			{
			case ePlayback::LOOP:
				m_frame = 0;
				break;
			case ePlayback::ONE_TIME:
				m_frame = (int)m_textures.size() - 1;
				break;
			case ePlayback::ONE_TIME_DESTROY:
				m_frame = (int)m_textures.size() - 1;
				m_sensei->SetState(Entity::DESTROY);
				break;
			case ePlayback::PING_PONG:
				m_frame = Math::Clamp(m_frame, 0,(int)m_textures.size() - 1);
				m_direction = -m_direction;
			}

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
