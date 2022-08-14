#include "pch.h"
#include "CrawlerEnemy.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "World.h"
#include "utils.h"
#include "Player.h"
#include "Matrix2x3.h"

CrawlerEnemy::CrawlerEnemy(const Point2f &position)
	: Enemy( position )
	, m_Speed{ 100.f }
	, m_Direction{ Direction::right }
{
	m_Velocity = Vector2f{ 1.f, 0.f };
	CalculateTexture("Crawler", 3);
}

CrawlerEnemy::~CrawlerEnemy()
{
}

void CrawlerEnemy::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Boundaries.left + m_Boundaries.width / 2, m_Boundaries.bottom + m_Boundaries.height / 2, 0);
		SetTextureRotation();
		glTranslatef(-(m_Boundaries.left + m_Boundaries.width / 2), -(m_Boundaries.bottom + m_Boundaries.height / 2), 0);
		Enemy::Draw();
	glPopMatrix();
}

void CrawlerEnemy::Update(float elapsedSec, World* level, Player* player)
{
	Enemy::Update(elapsedSec, level, player);
	Move(elapsedSec, level);
}

void CrawlerEnemy::Move(float elapsedSec, World* level)
{
	utils::HitInfo hitinfo_down;
	utils::HitInfo hitinfo_right;

	utils::HitInfo hitinfo_down_2;
	utils::HitInfo hitinfo_right_2;

	float detectionDistance = 2.f;
	bool isHittingDown{ false };
	bool isHittingRight{ false };	
	bool isHittingDown_2{ false };
	bool isHittingRight_2{ false };

	Point2f center{m_Boundaries.left + m_Boundaries.width / 2, m_Boundaries.bottom + m_Boundaries.height / 2 };

	Point2f ray_up{ m_Boundaries.left + m_Boundaries.width * 0.9f , m_Boundaries.bottom + m_Boundaries.height + detectionDistance };
	Point2f ray_down{ m_Boundaries.left + m_Boundaries.width * 0.9f , m_Boundaries.bottom - detectionDistance };
	Point2f ray_left{ m_Boundaries.left - detectionDistance, m_Boundaries.bottom + m_Boundaries.height * 0.9f };
	Point2f ray_right{ m_Boundaries.left + m_Boundaries.width + detectionDistance, m_Boundaries.bottom + m_Boundaries.height * 0.9f };

	Point2f ray_up_2{ m_Boundaries.left + m_Boundaries.width * 0.1f , m_Boundaries.bottom + m_Boundaries.height + detectionDistance };
	Point2f ray_down_2{ m_Boundaries.left + m_Boundaries.width * 0.1f , m_Boundaries.bottom - detectionDistance };
	Point2f ray_left_2{ m_Boundaries.left - detectionDistance, m_Boundaries.bottom + m_Boundaries.height * 0.1f };
	Point2f ray_right_2{ m_Boundaries.left + m_Boundaries.width + detectionDistance, m_Boundaries.bottom + m_Boundaries.height * 0.1f };

	switch (m_Direction)
	{
	case CrawlerEnemy::Direction::right:
		for (size_t i = 0; i < level->GetVertices().size(); i++)
		{
			if (utils::Raycast(level->GetVertices()[i], center, ray_right, hitinfo_right))
			{
				isHittingRight = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_right_2, hitinfo_right_2))
			{
				isHittingRight_2 = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_down, hitinfo_down))
			{
				isHittingDown = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_down_2, hitinfo_down_2))
			{
				isHittingDown_2 = true;
			}
		}
		if (isHittingRight)
		{
			m_Boundaries.left = hitinfo_right.intersectPoint.x - m_Boundaries.width;
			m_Velocity = Vector2f{ 0.f, 1.f };
			m_Direction = Direction::up;
		}
		else if (isHittingRight_2)
		{
			m_Boundaries.left = hitinfo_right_2.intersectPoint.x - m_Boundaries.width;
			m_Velocity = Vector2f{ 0.f, 1.f };
			m_Direction = Direction::up;
		}
		else if(!(isHittingDown || isHittingDown_2))
		{
			m_Boundaries.left += m_Boundaries.width / 2;
			m_Boundaries.bottom -= m_Boundaries.height / 2 - 1;
			m_Velocity = Vector2f{ 0.f, -1.f };
			m_Direction = Direction::down;
		}
		break;
	case CrawlerEnemy::Direction::down:
		for (size_t i = 0; i < level->GetVertices().size(); i++)
		{
			if (utils::Raycast(level->GetVertices()[i], center, ray_down, hitinfo_right))
			{
				isHittingRight = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_down_2, hitinfo_right_2))
			{
				isHittingRight_2 = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_left, hitinfo_down))
			{
				isHittingDown = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_left_2, hitinfo_down_2))
			{
				isHittingDown_2 = true;
			}
		}
		if (isHittingRight)
		{
			m_Boundaries.bottom = hitinfo_right.intersectPoint.y;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		else if (isHittingRight_2)
		{
			m_Boundaries.bottom = hitinfo_right_2.intersectPoint.y;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{

			m_Boundaries.left -= m_Boundaries.width / 2 - 1;
			m_Boundaries.bottom -= m_Boundaries.height / 2;
			m_Velocity = Vector2f{ -1.f, 0.f };
			m_Direction = Direction::left;
		}
		break;
	case CrawlerEnemy::Direction::left:
		for (size_t i = 0; i < level->GetVertices().size(); i++)
		{
			if (utils::Raycast(level->GetVertices()[i], center, ray_left, hitinfo_right))
			{
				isHittingRight = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_left_2, hitinfo_right_2))
			{
				isHittingRight_2 = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_up, hitinfo_down))
			{
				isHittingDown = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_up_2, hitinfo_down_2))
			{
				isHittingDown_2 = true;
			}
		}
		if (isHittingRight)
		{
			m_Boundaries.left = hitinfo_right.intersectPoint.x;
			m_Velocity = Vector2f{ 0.f, -1.f };
			m_Direction = Direction::down;
		}
		else if (isHittingRight_2)
		{
			m_Boundaries.left = hitinfo_right_2.intersectPoint.x;
			m_Velocity = Vector2f{ 0.f, -1.f };
			m_Direction = Direction::down;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{
			m_Boundaries.left -= m_Boundaries.width / 2;
			m_Boundaries.bottom += m_Boundaries.height / 2 + 1;
			m_Velocity = Vector2f{ 0.f, 1.f };
			m_Direction = Direction::up;
		}
		break;
	case CrawlerEnemy::Direction::up:
		for (size_t i = 0; i < level->GetVertices().size(); i++)
		{
			if (utils::Raycast(level->GetVertices()[i], center, ray_up, hitinfo_right))
			{
				isHittingRight = true;
			}			
			else if (utils::Raycast(level->GetVertices()[i], center, ray_up_2, hitinfo_right_2))
			{
				isHittingRight_2 = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_right, hitinfo_down))
			{
				isHittingDown = true;
			}
			else if (utils::Raycast(level->GetVertices()[i], center, ray_right_2, hitinfo_down_2))
			{
				isHittingDown_2 = true;
			}
		}
		if (isHittingRight)
		{
			m_Boundaries.bottom = hitinfo_right.intersectPoint.y - m_Boundaries.height;
			m_Velocity = Vector2f{ -1.f, 0.f };
			m_Direction = Direction::left;
		}
		else if (isHittingRight_2)
		{
			m_Boundaries.bottom = hitinfo_right_2.intersectPoint.y - m_Boundaries.height;
			m_Velocity = Vector2f{ -1.f, 0.f };
			m_Direction = Direction::left;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{
			m_Boundaries.left += m_Boundaries.width / 2 + 1;
			m_Boundaries.bottom += m_Boundaries.height / 2;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		break;
	default:
		break;
	}
	
	m_Boundaries.left += m_Velocity.x * m_Speed * elapsedSec;
	m_Boundaries.bottom += m_Velocity.y * m_Speed * elapsedSec;

	m_Position.x = m_Boundaries.left;
	m_Position.y = m_Boundaries.bottom;
}

void CrawlerEnemy::SetTextureRotation() const
{
	switch (m_Direction)
	{
	case CrawlerEnemy::Direction::right:
		glRotatef(0, 0, 0, 1);
		break;
	case CrawlerEnemy::Direction::left:
		glRotatef(180, 0, 0, 1);
		break;
	case CrawlerEnemy::Direction::down:
		glRotatef(-90, 0, 0, 1);
		break;
	case CrawlerEnemy::Direction::up:
		glRotatef(90, 0, 0, 1);
		break;
	default:
		break;
	}
}
