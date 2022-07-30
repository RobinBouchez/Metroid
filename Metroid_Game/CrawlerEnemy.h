#pragma once

class Enemy;
class World;

class CrawlerEnemy : virtual public Enemy
{
public:
	enum class CrawlerDirection
	{
		right = 0, down = 1, left = 2, up = 3
	};

	CrawlerEnemy(Point2f &position);
	virtual ~CrawlerEnemy();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level);
	void Move(float elapsedSec, World* level);

private:
	CrawlerDirection m_Direction;
	float m_Speed;

	void SetTextureRotation() const;
};

