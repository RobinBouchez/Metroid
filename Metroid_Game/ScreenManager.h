#pragma once
#include "Manager.h"
#include <vector>

class Screen;

class ScreenManager final : public Manager<ScreenManager>
{
public:
	ScreenManager() = default;
	~ScreenManager() = default;
	ScreenManager(const ScreenManager&) = delete;
	ScreenManager& operator=(const ScreenManager&) = delete;
	ScreenManager(ScreenManager&&) = delete;
	ScreenManager& operator=(ScreenManager&&) = delete;
	
	Screen* GetCurrent();
	void Add(Screen* screen);
	void Draw() const;
	void Remove();
	void Replace(Screen* screen);
	void Update(float elapsedSec);
	void Cleanup();

private:
	std::vector<Screen*> m_ScreenVector;
};

