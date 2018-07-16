#pragma once
#include "singleton.h"
#include "engine.h"
#include "text.h"
#include <vector>

class Textmanager : public Singleton<Textmanager>
{
public:
	Textmanager(){}
	~Textmanager(){}

	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

protected:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};

