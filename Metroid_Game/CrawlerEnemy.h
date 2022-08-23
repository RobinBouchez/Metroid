#pragma once
#include "Enemy.h"

class CrawlerPickUp;

class CrawlerEnemy final : public Enemy
{
public:
	enum class Direction
	{
		right = 0, down = 1, left = 2, up = 3
	};

	CrawlerEnemy(const Point2f &position);
	virtual ~CrawlerEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level, Player* player) override;

private:
	Direction m_Direction;
	CrawlerPickUp* m_PickUp;
	const float m_Speed;

	void Move(float elapsedSec, World* level);
	void SetTextureRotation() const;
};

