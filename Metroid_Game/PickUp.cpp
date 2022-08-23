#include "pch.h"
#include "PickUp.h"

PickUp::PickUp(const Point2f& position)
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
