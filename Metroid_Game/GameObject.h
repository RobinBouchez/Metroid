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

	const Point2f GetPosition();
	const void SetPosition(const Point2f& pos);

protected:
	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;


	Rectf GetBoundaries();
	Vector2f GetVelocity();

	static bool m_IsOnGround;
	static const float m_Gravity;
	
	bool m_IsMovingLeft;

	float m_HorizontalSpeed;
	float m_JumpSpeed;
	
	Vector2f m_Acceleration;
	Vector2f m_Velocity;

private:
	Rectf m_Boundaries;

	Point2f m_Position;

};

