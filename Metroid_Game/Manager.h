#pragma once
template<typename T>
class Manager
{
public:
	virtual ~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	Manager(Manager&&) = delete;
	Manager& operator=(Manager&&) = delete;

	static T& GetInstance();

protected:
	Manager() = default;
};

template<typename T>
inline T& Manager<T>::GetInstance()
{
	static T instance{};
	return instance;
}
