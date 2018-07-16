#pragma once
#include "engine.h"
#include "singleton.h"
#include "color.h"
#include "vector2D.h"

class Renderer : public Singleton<Renderer>
{
public:
	Renderer(){}
	~Renderer(){}

	SDL_Renderer* GetRenderer() { return m_renderer; }
	bool Initalize(Engine* engine);
	void Shutdown();

	void BeginFrame();
	void EndFrame();

	void SetColor(const Color & color);

	void DrawTexture(SDL_Texture* texture, const Vector2D& position, const Vector2D& scale, float angle);
	void DrawTexure(SDL_Texture* texture, const Vector2D&position, float angle);
	void DrawText();
	friend Singleton<Renderer>;
public:
	Engine * m_engine;
	SDL_Renderer* m_renderer = nullptr;
};

