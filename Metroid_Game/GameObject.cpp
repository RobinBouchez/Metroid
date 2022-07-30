#include "pch.h"
#include "GameObject.h"

bool GameObject::m_IsOnGround = false;
//bool GameObject::m_Gravity = 9.81f;

GameObject::GameObject()
	: m_Boundaries{}
	, m_Acceleration{ 30.f , -9.810f }
	, m_Velocity{ 0.f,0.f }
	, m_IsMovingLeft{false}
	, m_HorizontalSpeed{ 350.f }
	, m_JumpSpeed{ 800.f }
{
}

GameObject::~GameObject()
{

}
