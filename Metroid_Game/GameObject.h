#pragma once
#include "Vector2f.h"

class GameObject
{
public:

	GameObject();
	virtual ~GameObject() = default;
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(GameObject&&) = delete;

protected:
	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;

	static bool m_IsOnGround;
	static const float m_Gravity;
	
	Rectf m_Boundaries;

	bool m_IsMovingLeft;

	float m_HorizontalSpeed;
	float m_JumpSpeed;
	
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
};

