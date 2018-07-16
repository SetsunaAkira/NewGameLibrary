#pragma once
#include "singleton.h"
#include "fmod.hpp"
#include "engine.h"

#include <string>
#include <map>

class ENGINE_API Audiosystem : public Singleton<Audiosystem>
{
public:
	Audiosystem(){}
	~Audiosystem(){}

	bool Initalize(Engine* engine);
	void Update();
	void Shutdown();

	void AddSound(const std::string& id, const std::string& filename);
	void PlaySound(const std::string& id, bool loop);
	void RemoveSound(const std::string& id);

	friend Singleton<Audiosystem>;

protected:
FMOD::System* m_fmodSystem;
std::map<std::string, FMOD::Sound*> m_sounds;

private:
	Engine * m_engine;
};

class audiosystem
{
public:
	audiosystem(){}
	~audiosystem(){}
};

