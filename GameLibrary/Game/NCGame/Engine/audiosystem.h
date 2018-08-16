#pragma once
#include "engine.h"
#include "singleton.h"
#include "audio.h"
#include <fmod.hpp>
#include <fmod_common.h>
#include <string>
#include <vector>
#include <map>

class ENGINE_API Audiosystem : public Singleton<Audiosystem>
{
public:
	bool Initalize(Engine* engine);
	void Update();
	void Shutdown();

	void AddSound(const std::string& id, const std::string& filename);
	void PlaySound(const std::string& id, bool loop);
	void RemoveSound(const std::string& id);

	friend Singleton<Audiosystem>;

protected:
	Audiosystem() {}

private:
	Engine * m_engine;

	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};
