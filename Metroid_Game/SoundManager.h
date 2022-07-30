#pragma once
#include <unordered_map>

class SoundEffect;
class SoundManager
{
public:
	SoundManager(const std::string& filename);
	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager();

	void Play(std::string soundName);
	void PlayLoop(std::string soundName);

	void SetVolume(int volume);

private:
	std::unordered_map<std::string, SoundEffect*> m_pSoundEffects;

	void CreateSound(const std::string& filename);
};