#pragma once
#include "Enemy.h"

class World;

class CrawlerEnemy : virtual public Enemy
{
public:
	enum class Direction
	{
		right = 0, down = 1, left = 2, up = 3
	};

	CrawlerEnemy(const Point2f &position);
	virtual ~CrawlerEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:
	float m_Speed;
	Direction m_Direction;

	void Move(float elapsedSec, World* level);
	void Update(float elapsedSec, World* level);
	void SetTextureRotation() const;
};

