#pragma once
template<typename T>
class Settings final
{
public:
	Settings() = default;
	~Settings() = default;
	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;
	Settings(Settings&&) = delete;
	Settings& operator=(Settings&&) = delete;

	static T& GetInstance();
};

