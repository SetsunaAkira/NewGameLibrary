#include "textComponent.h"
#include "transform.h"
#include "entity.h"

void TextComponent::Create(const std::string& text, const std::string& fontname, int fontsize, const Color& color, const Vector2D origin)
{
	m_text = new Text();
	m_text->Create(text, fontname, fontsize, color);
}

void TextComponent::Destroy()
{
}

void TextComponent::Update()
{
}

void TextComponent::Draw()
{
	Transform transform = m_sensei->GetTransform();
	m_text->Draw(transform.position, m_origin,transform.scale,transform.rotation);
}

void TextComponent::SetText(const std::string & text)
{
	m_text->SetText(text);
}

void TextComponent::SetColor(const Color & color)
{
	m_text->SetColor(color);
}
