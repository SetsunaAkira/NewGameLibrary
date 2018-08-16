#pragma once
#include "singleton.h"
#include "engine.h"
#include "text.h"
#include <vector>

class ENGINE_API Textmanager : public Singleton<Textmanager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<Textmanager>;

protected:
	Textmanager() {}

private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};

