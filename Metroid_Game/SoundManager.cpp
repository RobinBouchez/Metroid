#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"

SoundManager::SoundManager()
{
	Initialize();
}

SoundManager::~SoundManager()
{
	for (std::pair<std::string, SoundEffect*> e: m_pSoundEffects)
	{
		delete e.second;
		e.second = nullptr;
	}
}

void SoundManager::Initialize()
{
	m_pSoundEffects["Music"] = new SoundEffect("Resources/Sound/Music.mp3");
	m_pSoundEffects["Jump"] = new SoundEffect("Resources/Sound/Jump.wav");
	m_pSoundEffects["Roll"] = new SoundEffect("Resources/Sound/Roll.wav");
	m_pSoundEffects["PickUp"] = new SoundEffect("Resources/Sound/PickUp.wav");
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
