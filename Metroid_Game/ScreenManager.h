#pragma once
#include "Manager.h"

class ScreenManager final : public Manager<ScreenManager>
{
public:
	ScreenManager() = default;
	~ScreenManager() = default;
	ScreenManager(const ScreenManager&) = delete;
	ScreenManager& operator=(const ScreenManager&) = delete;
	ScreenManager(ScreenManager&&) = delete;
	ScreenManager& operator=(ScreenManager&&) = delete;
	
protected:

};

