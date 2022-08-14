#pragma once
#include "Enemy.h"

class SkrullEnemy : public Enemy
{
public:
	SkrullEnemy(const Point2f& position);
	virtual ~SkrullEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level, Player* player);
private:
};

