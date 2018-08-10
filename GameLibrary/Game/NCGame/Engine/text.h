#pragma once
#include <string>
#include "vector2D.h"
#include "color.h"
#include "SDL_ttf.h"
#include "texture.h"
class ENGINE_API Text
{
public:
	Text();
	~Text();
	void Create(const std::string& text, const std::string& fontName, int size, const Color& color);

	void Draw(const Vector2D& position, const Vector2D& origin = Vector2D::zero, const Vector2D& scale = Vector2D::one, float angle = 0);


	void SetText(const std::string& text);
	void SetText(const std::string& text, const Color& color);
	void SetColor(const Color& color);

protected:
	void CreateTexture();

protected:
	Texture * m_texture = nullptr;
	TTF_Font * m_font = nullptr;
	std::string m_text;
	Color m_color;
};


