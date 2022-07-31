#pragma once
#include "Enemy.h"

class World;

class SkrullEnemy : virtual public Enemy
{
public:
	SkrullEnemy(const Point2f& position);
	virtual ~SkrullEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level);
private:
};

