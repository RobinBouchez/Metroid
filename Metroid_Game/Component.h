#pragma once
#include "GameObject.h"

//template<typename T>
class Component : public GameObject
{
public:
	Component() = default;
	virtual ~Component() = default;
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;

	//static T& GetInstance();
protected:
	Component(GameObject* object) : GameObject(*object) {};

	Component& Create();
	Component& Get();
	void Set(const Component& component);

	//virtual void Update(float elapsedSec) override;
	//GameObject* m_GameObject;
};

//template<typename T>
//inline T& Component<T>::GetInstance()
//{
//	static T instance{};
//	return instance;
//}

//template<typename T>
//inline Component<T>::Component(GameObject* object)
//	:m_GameObject(object)
//{
//}

//template<typename T>
//inline void Component<T>::Update(float elapsedSec)
//{
//	m_GameObject->Update(elapsedSec);
//}

