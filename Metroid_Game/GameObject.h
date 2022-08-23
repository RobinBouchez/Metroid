#pragma once
#include "Vector2f.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;
	GameObject(const GameObject&) = default;
	GameObject& operator=(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	const  Rectf GetBoundaries() const;

	bool GetIsActive() const;
	void SetIsActive(bool value);

protected:
	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;


	static bool m_IsOnGround;
	static const float m_Gravity;
	
	Vector2f m_Acceleration;
	Vector2f m_Velocity;

	float m_Width;
	float m_Height;

	bool m_IsActive;

	Point2f m_Position;
};

