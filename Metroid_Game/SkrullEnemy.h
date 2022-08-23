#pragma once
#include "Enemy.h"

class SkrullEnemy final : public Enemy
{
public:
	SkrullEnemy(const Point2f& position);
	virtual ~SkrullEnemy() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, World* level, Player* player);

	//Point2f m_Position;
private:
	const float m_DetectionRadius;
	float m_AttackSpeed;
};

