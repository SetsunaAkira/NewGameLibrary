#include "renderer.h"
#include "SDL_ttf.h"
#include <SDL_image.h>

bool Renderer::Initalize(Engine * engine)
{
	m_engine = engine;
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	m_renderer = SDL_CreateRenderer(m_engine->GetWindow(), -1, 0);

	return true;
}

void Renderer::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}

void Renderer::SetColor(const Color & color)
{
	SDL_SetRenderDrawColor(m_renderer, color.ConvertU8(0), color.ConvertU8(1), color.ConvertU8(2), 255);
}

void Renderer::DrawTexture(SDL_Texture * texture, const Vector2D & position, const Vector2D & scale, float angle)
{
	SDL_Point point = position * scale;
	SDL_Rect dest = { point.x, point.y, 0, 0 };
	SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::DrawTexture(Texture * texture, const Vector2D & position, const Vector2D & scale, float angle)
{
	DrawTexture(texture->m_sdlTexture, position, scale, angle);
}

void Renderer::DrawTexure(SDL_Texture * texture, const Vector2D & position, float angle)
{
	SDL_Point point = position;
	SDL_Rect dest = { point.x, point.y, 0, 0 };
	SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}

