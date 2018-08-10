#pragma once
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"
#include "color.h"
#include "text.h"
class Texture;

class ENGINE_API TextComponent : public IRenderComponent
{
public:
	TextComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& text, const std::string& fontname, int fontsize, const Color& color, const Vector2D origin = Vector2D::zero);
	void Destroy();
	void Update();

	void Draw();

	void SetText(const std::string & text);
	void SetColor(const Color & color);

protected:
	Vector2D m_origin;
	Texture* m_texture;
	Text* m_text;
};
