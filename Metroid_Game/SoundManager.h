#pragma once
#include <unordered_map>
#include "Manager.h"

class SoundEffect;
class SoundManager final : public Manager<SoundManager>
{
public:
	SoundManager() = default;
	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager();
	
	SoundEffect* CreateSound(const std::string& filename);

	void Play(std::string soundName);
	void PlayLoop(std::string soundName);

	void SetVolume(int volume);

	void Cleanup();

private:
	std::unordered_map<std::string, SoundEffect*> m_pSoundEffects;

};