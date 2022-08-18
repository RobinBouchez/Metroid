#include "pch.h"
#include "Movement.h"

Movement::Movement()
{
}

void Movement::Update(float elapsedSec)
{
    //Component::Update(elapsedSec);
}

const Vector2f& Movement::GetVelocity() const
{
    return m_Velocity;
}

const void Movement::SetVelocity(const Vector2f& value)
{
    m_Velocity = value;
}
