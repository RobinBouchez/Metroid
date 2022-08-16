#include "pch.h"
#include "ScreenManager.h"
#include "Screen.h"

void ScreenManager::Add(Screen* screen)
{
	m_ScreenVector.push_back(screen);
}

void ScreenManager::Draw() const
{
	if (!m_ScreenVector.empty())
	{
		m_ScreenVector.back()->Draw();
	}
}

void ScreenManager::Remove()
{
	if (!m_ScreenVector.empty())
	{
		delete m_ScreenVector.back();
		m_ScreenVector.back() = nullptr;
		m_ScreenVector.pop_back();
	}
}

void ScreenManager::Replace(Screen* screen)
{
	this->Remove();
	this->Add(screen);
}

void ScreenManager::Update(float elapsedSec)
{
	if (!m_ScreenVector.empty())
	{
		m_ScreenVector.back()->Update(elapsedSec);
	}
}

void ScreenManager::Cleanup()
{
	if (!m_ScreenVector.empty())
	{
		for (auto e : m_ScreenVector) {
			delete e;
			e = nullptr;
		}
		m_ScreenVector.clear();
	}
}

Screen* ScreenManager::GetCurrent()
{
	if (!m_ScreenVector.empty())
	{
		return m_ScreenVector.back();
	}
	return nullptr;
}