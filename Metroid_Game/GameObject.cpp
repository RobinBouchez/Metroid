#include "pch.h"
#include "GameObject.h"

#include <functional>

bool GameObject::m_IsOnGround = false;

GameObject::GameObject()
	: m_Acceleration{ 30.f , -9.f }
	, m_Velocity{ 0.f, 0.f }
	, m_Position{}
	, m_Height{}
	, m_Width{}
	, m_IsActive{ true }
{
}

const Rectf GameObject::GetBoundaries() const
{
	return Rectf{ m_Position.x, m_Position.y, m_Width, m_Height };
}

bool GameObject::GetIsActive() const
{
	return m_IsActive;
}

void GameObject::SetIsActive(bool value)
{
	m_IsActive = value;
}
