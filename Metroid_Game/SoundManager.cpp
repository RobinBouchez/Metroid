#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"

SoundManager::SoundManager(const std::string& filename)
{
	CreateSound(filename);
}

SoundManager::~SoundManager()
{
	for (std::pair<std::string, SoundEffect*> e: m_pSoundEffects)
	{
		delete e.second;
		e.second = nullptr;
	}
}

void SoundManager::CreateSound(const std::string& filename)
{
	m_pSoundEffects[filename] = new SoundEffect("Resources/Sound/" + filename + ".wav");
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
