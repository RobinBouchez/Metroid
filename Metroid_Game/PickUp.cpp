#include "pch.h"
#include "PickUp.h"

PickUp::PickUp(const Point2f& position)
	: m_IsActive{ false }
	, m_Position{ position }
{

}

PickUp::~PickUp()
{
}

void PickUp::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}
}

void PickUp::Update(float elapsedSec)
{
}
