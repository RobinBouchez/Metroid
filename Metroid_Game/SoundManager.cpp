#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"

SoundManager::~SoundManager()
{
}

SoundEffect* SoundManager::CreateSound(const std::string& filename)
{
	if (m_pSoundEffects.find(filename) == m_pSoundEffects.end())
	{
		m_pSoundEffects.emplace(filename, new SoundEffect("Resources/Sound/" + filename + ".wav"));
	}
	return m_pSoundEffects[filename];
}

void SoundManager::Play(std::string soundName)
{
	m_pSoundEffects.at(soundName)->Play(0);
}

void SoundManager::PlayLoop(std::string soundName)
{
	m_pSoundEffects.at(soundName)->Play(INFINITE);
}

void SoundManager::SetVolume(int volume)
{
	for (std::pair<std::string, SoundEffect*> e : m_pSoundEffects)
	{
		e.second->SetVolume(volume);
	}
}

void SoundManager::Cleanup()
{
	for (auto& e : m_pSoundEffects)
	{
		delete e.second;
		e.second = nullptr;
	}
}
