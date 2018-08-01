#include "audiosystem.h"
#include <assert.h>


bool Audiosystem::Initalize(Engine * engine)
{
	void *extradriverdata = nullptr;
	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	assert(result == FMOD_OK);
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	assert(result == FMOD_OK);

	m_engine = engine;
	return true;
}

void Audiosystem::Update()
{
	FMOD_RESULT result = m_fmodSystem->update();
	assert(result == FMOD_OK);
}

void Audiosystem::Shutdown()
{
	for (auto& sound : m_sounds)
	{
		sound.second->release();
	}
	m_sounds.clear();
}

void Audiosystem::AddSound(const std::string & id, const std::string & audioname)
{
	assert(m_sounds.find(id) == m_sounds.end());
	FMOD::Sound* fmodsound = nullptr;
	FMOD_RESULT result = m_fmodSystem->createSound(audioname.c_str(), FMOD_DEFAULT, 0, &fmodsound);
	if (result == FMOD_OK)
	{
		m_sounds[id] = fmodsound;
	}
	
}

void Audiosystem::PlaySound(const std::string & id, bool loop)
{
	assert(m_sounds.find(id) != m_sounds.end());
	FMOD::Channel* channel;
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* fmodSound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		fmodSound->setMode(mode);
		FMOD_RESULT result = m_fmodSystem->playSound(fmodSound, 0, false, &channel);
		assert(result == FMOD_OK);
	}
}

void Audiosystem::RemoveSound(const std::string & id)
{
	assert(m_sounds.find(id) != m_sounds.end());
	
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* fmodSound = iter->second;
		FMOD_RESULT result = fmodSound->release();
		assert(result == FMOD_OK);
		m_sounds.erase(iter);
	}
}


