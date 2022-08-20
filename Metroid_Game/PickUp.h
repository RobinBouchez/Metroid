#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	PickUp(const Point2f& position);
	virtual ~PickUp();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	Rectf GetShape() const;

	bool m_IsActive;

protected:
	Point2f m_Position;
	Rectf m_Shape;

};

