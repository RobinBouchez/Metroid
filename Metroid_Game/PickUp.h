#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	PickUp(const Point2f& position);
	virtual ~PickUp() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
};

