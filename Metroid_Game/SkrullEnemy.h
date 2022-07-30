#pragma once
#include "Enemy.h"

class World;

class SkrullEnemy : virtual public Enemy
{
public:
	enum class Direction
	{
		right = 0, down = 1, left = 2, up = 3
	};

	SkrullEnemy(Point2f& position);
	virtual ~SkrullEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level);

private:
	Direction m_Direction;
};

