#include "pch.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"
#include "utils.h"
#include "Player.h"
#include "World.h"

SkrullEnemy::SkrullEnemy(const Point2f& position)
	: Enemy(position)
	, m_DetectionRadius{ 500.f }
	, m_AttackSpeed{ 6.f }
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
	

	float distance = utils::GetDistance(Point2f{ this->m_Position.x, this->m_Position.y}, Point2f{player->m_Shape.left + player->m_Shape.width / 2, player->m_Shape.bottom + player->m_Shape.height / 2});

	if (level->IsOnGround(this->GetBoundaries()))
	{
		return;
	}

	m_AttackSpeed += elapsedSec;

	if (distance <= m_DetectionRadius)
	{
		Vector2f direction{ player->m_Shape.left - this->m_Position.x, player->m_Shape.bottom - this->m_Position.y };
		
		direction = direction.Normalized();

		const float m_SafeRadius = player->m_Shape.height;
		if (distance <= m_SafeRadius)
		{
			this->m_Position.y -= 1.f * m_AttackSpeed;
			return;
		}

		this->m_Position.x += direction.x * m_AttackSpeed;
		this->m_Position.y += direction.y * m_AttackSpeed;
	}
}
