#include "pch.h"
#include "LevelManager.h"
#include "Level.h"

Level* LevelManager::GetCurrent() const
{
	if (!m_LevelVector.empty())
	{
		return m_LevelVector.back();
	}
	return nullptr;
}

void LevelManager::Add(Level* level)
{
    m_LevelVector.push_back(level);
}

void LevelManager::Draw() const
{
	if (!m_LevelVector.empty())
	{
		m_LevelVector.back()->Draw();
	}
}

void LevelManager::Remove()
{
	if (!m_LevelVector.empty())
	{
		delete m_LevelVector.back();
		m_LevelVector.back() = nullptr;
		m_LevelVector.pop_back();
	}
}

void LevelManager::Replace(Level* level)
{
	this->Remove();
	this->Add(level);
}

void LevelManager::Update(float elapsedSec)
{
	if (!m_LevelVector.empty())
	{
		m_LevelVector.back()->Update(elapsedSec);
	}
}

void LevelManager::Cleanup()
{
	if (!m_LevelVector.empty())
	{
		for (auto e : m_LevelVector) {
			delete e;
			e = nullptr;
		}
		m_LevelVector.clear();
	}
}
