#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	PickUp(const Point2f& position);
	virtual ~PickUp();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

protected:
	bool m_IsActive;
	Point2f m_Position;

};

