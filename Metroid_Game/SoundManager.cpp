#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"

SoundEffect* SoundManager::CreateSound(const std::string& filename, const std::string& type)
{
	if (m_pSoundEffects.find(filename) == m_pSoundEffects.end())
	{
		m_pSoundEffects.emplace(filename, new SoundEffect("Resources/Sound/" + filename + type));
	}
	return m_pSoundEffects[filename];
}

void SoundManager::Play(const std::string& soundName)
{
	if (m_pSoundEffects.at(soundName)->IsLoaded())
	{
		m_pSoundEffects.at(soundName)->Play(0);
	}
}

void SoundManager::PlayLoop(const std::string& soundName)
{
	if (m_pSoundEffects.at(soundName)->IsLoaded())
	{
		m_pSoundEffects.at(soundName)->Play(1);
	}
}

void SoundManager::SetVolume(const int& volume)
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
	m_pSoundEffects.clear();
}
