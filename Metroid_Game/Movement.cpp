#include "pch.h"
#include "Movement.h"

Movement::Movement() 
    : m_Velocity{}
    , m_Acceleration{}
{
}

Vector2f Movement::GetVelocity() const
{
    return m_Velocity;
}

void Movement::SetVelocity(const Vector2f& value)
{
    m_Velocity = value;
}
