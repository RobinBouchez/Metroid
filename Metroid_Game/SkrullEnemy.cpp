#include "pch.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"
#include "utils.h"
#include "Player.h"
#include "World.h"

SkrullEnemy::SkrullEnemy(const Point2f& position)
	: Enemy(position)
	, m_DetectionRadius{ 500.f }
	, m_AttackSpeed{ 4.f }
{
	m_Position = position;
	m_Tag = "Skrull";

	CalculateTexture(m_Tag, 3);
	m_Width = 70.f;
	m_Height = 70.f;
}

void SkrullEnemy::Draw() const
{
	Enemy::Draw();
}

void SkrullEnemy::Update(float elapsedSec, World* level, Player* player)
{
	Enemy::Update(elapsedSec, level, player);
	
	float distance = utils::GetDistance(Point2f{m_Position.x, m_Position.y}, Point2f{player->m_Shape.left, player->m_Shape.bottom});

	if (level->IsOnGround(player->m_Shape))
	{
		return;
	}

	if (distance <= m_DetectionRadius)
	{
		Vector2f direction{ player->m_Shape.left - m_Position.x, player->m_Shape.bottom - m_Position.y };
		
		direction = direction.Normalized();

		m_Position.x += direction.x * m_AttackSpeed;
		m_Position.y += direction.y * m_AttackSpeed;
	}
}
