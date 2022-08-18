#pragma once
#include "Vector2f.h"
#include "Component.h"

class Movement final //: public Component<Movement>
{
public:
	Movement();
	~Movement() = default;

	virtual void Update(float elapsedSec);// override;

	const Vector2f& GetVelocity() const;
	const void SetVelocity(const Vector2f& value);


private:
	Vector2f m_Velocity;
};

