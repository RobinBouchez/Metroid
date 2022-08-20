#include "pch.h"
#include "GameObject.h"

bool GameObject::m_IsOnGround = false;

GameObject::GameObject()
	: m_Boundaries{}
	, m_Acceleration{ 30.f , -9.810f }
	, m_Velocity{ 0.f,0.f }
	, m_IsMovingLeft{false}
	, m_HorizontalSpeed{ 300.f }
	, m_Position{}
{
}

const Point2f GameObject::GetPosition()
{
	return m_Position;
}

const Rectf GameObject::GetBounds()
{
	return Rectf{ m_Position.x, m_Position.y, m_Width, m_Height };
}

const void GameObject::SetPosition(const Point2f& pos)
{
	m_Position = pos;
}

Rectf GameObject::GetBoundaries()
{
	return m_Boundaries;
}

Vector2f GameObject::GetVelocity()
{
	return m_Velocity;
}
