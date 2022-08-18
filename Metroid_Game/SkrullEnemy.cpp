#include "pch.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"
#include "utils.h"
#include "Player.h"

SkrullEnemy::SkrullEnemy(const Point2f& position)
	: Enemy(position)
{
	CalculateTexture("Skrull", 3);
	m_Boundaries = Rectf{ position.x, position.y, 70, 70 };
}

void SkrullEnemy::Draw() const
{
	Enemy::Draw();
}

void SkrullEnemy::Update(float elapsedSec, World* level, Player* player)
{
	Enemy::Update(elapsedSec, level, player);
	
	float detectionRadius = 500;
	float stopRadius = 10;

	utils::GetDistance(m_Position, Point2f{ player->GetShape().left, player->GetShape().bottom });

}
