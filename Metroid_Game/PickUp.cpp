#include "pch.h"
#include "PickUp.h"

PickUp::PickUp(const Point2f& position)
	: m_IsActive{ true }
	, m_Position{ position }
	, m_Shape{}
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

Rectf PickUp::GetShape() const
{
	return m_Shape;
}
