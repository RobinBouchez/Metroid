#include "pch.h"
#include "Vitals.h"

Vitals::Vitals(const float& health)
    : m_Health{ health }
    , m_State{ State::alive }
{
}

Vitals::~Vitals()
{

}

const float Vitals::GetHealth() const
{
    return m_Health;
}

void Vitals::SetHealth(const float& value)
{
    m_Health = value;
}

