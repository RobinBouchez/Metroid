#pragma once
#include "Vector2f.h"

class Movement final
{
public:
	Movement();
	~Movement() = default;

	virtual void Update(float elapsedSec) = 0;

	Vector2f GetVelocity() const;
	void SetVelocity(const Vector2f& value);

private:
	Vector2f m_Velocity;
	Vector2f m_Acceleration;

	const float Speed{};
};

