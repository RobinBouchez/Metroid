#include "pch.h"
#include "Vitals.h"

Vitals::Vitals(const float& health)
    : m_Health{ health }
    , m_State{ State::alive }
    , m_InvinsibleTimer{ 0.f }
    , m_InvinsibleDuration{ 1.f }
    , m_TakenDamage{ false }
{
}

Vitals::~Vitals()
{

}

void Vitals::Update(float elapsedSec)
{
    if (m_TakenDamage)
    {
        m_InvinsibleTimer += elapsedSec;

        if (m_InvinsibleTimer >= m_InvinsibleDuration)
        {
            m_TakenDamage = false;
            m_InvinsibleTimer = 0.f;
        }
    }
}

const float Vitals::GetHealth() const
{
    return m_Health;
}

void Vitals::SetHealth(const float& value)
{
    m_Health = value;
}

void Vitals::TakeDamage(const float& damage)
{
    if (!m_TakenDamage)
    {
        m_Health -= damage;
        m_TakenDamage = true;
    }
}

