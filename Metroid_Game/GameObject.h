#pragma once
#include "Vector2f.h"

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Draw() const = 0;

protected:
	static bool m_IsOnGround;
	static const float m_Gravity;
	
	Rectf m_Boundaries;

	bool m_IsMovingLeft;

	float m_HorizontalSpeed;
	float m_JumpSpeed;
	
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
};

