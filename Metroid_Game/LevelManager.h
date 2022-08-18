#pragma once
#include "Manager.h"

#include <vector>

class Level;

class LevelManager final : Manager< LevelManager>
{
public:

	LevelManager() = default;
	~LevelManager() = default;
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	LevelManager(LevelManager&&) = delete;
	LevelManager& operator=(LevelManager&&) = delete;


public:
	
	Level* GetCurrent();
	void Add(Level* level);
	void Draw() const;
	void Remove();
	void Replace(Level* level);
	void Update(float elapsedSec);
	void Cleanup();

private:
	std::vector<Level*> m_LevelVector;
};