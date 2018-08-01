#pragma once
#include "engine.h"
#include "singleton.h"
#include <string>
class ENGINE_API fileSystem : public Singleton<fileSystem>
{
public:
	fileSystem(){}
	~fileSystem(){}

	bool Initialize(Engine * engine);
	void Update();
	void Shutdown();

	void setPathname(const std::string& pathname) { m_pathname = pathname; }
	const std::string& getPathname() { return m_pathname; }
protected:
	Engine * m_engine;
	std::string m_pathname;
};

