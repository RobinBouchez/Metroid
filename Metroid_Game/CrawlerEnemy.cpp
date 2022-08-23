#include "pch.h"
#include "CrawlerEnemy.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "World.h"
#include "utils.h"
#include "Player.h"
#include "Matrix2x3.h"
#include "CrawlerPickUp.h"
#include "PickUp.h"
#include "PickUpManager.h"
#include "Vitals.h"

CrawlerEnemy::CrawlerEnemy(const Point2f &position)
	: Enemy( position )
	, m_Speed{ 100.f }
	, m_Direction{ Direction::right }
	, m_PickUp{ nullptr }
{
	m_Velocity = Vector2f{ 1.f, 0.f };
	m_Position = position;
	m_Tag = "Crawler";
	CalculateTexture(m_Tag, 3);
}

CrawlerEnemy::~CrawlerEnemy()
{
}

void CrawlerEnemy::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0);
		SetTextureRotation();
		glTranslatef(-(m_Position.x + m_Width / 2), -(m_Position.y + m_Height / 2), 0);
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

	float detectionDistance = 1.8f;
	bool isHittingDown{ false };
	bool isHittingRight{ false };	
	bool isHittingDown_2{ false };
	bool isHittingRight_2{ false };

	Point2f center{m_Position.x + m_Width / 2, m_Position.y + m_Height / 2 };

	Point2f ray_up{ m_Position.x + m_Width * 0.9f , m_Position.y + m_Height + detectionDistance };
	Point2f ray_down{ m_Position.x + m_Width * 0.9f , m_Position.y - detectionDistance };
	Point2f ray_left{ m_Position.x - detectionDistance, m_Position.y + m_Height * 0.9f };
	Point2f ray_right{ m_Position.x + m_Width + detectionDistance, m_Position.y + m_Height * 0.9f };

	Point2f ray_up_2{ m_Position.x + m_Width * 0.1f , m_Position.y + m_Height + detectionDistance };
	Point2f ray_down_2{ m_Position.x + m_Width * 0.1f , m_Position.y - detectionDistance };
	Point2f ray_left_2{ m_Position.x - detectionDistance, m_Position.y + m_Height * 0.1f };
	Point2f ray_right_2{ m_Position.x + m_Width + detectionDistance, m_Position.y + m_Height * 0.1f };

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
			m_Position.x = hitinfo_right.intersectPoint.x - m_Width;
			m_Velocity = Vector2f{ 0.f, 1.f };
			m_Direction = Direction::up;
		}
		else if (isHittingRight_2)
		{
			m_Position.x = hitinfo_right_2.intersectPoint.x - m_Width;
			m_Velocity = Vector2f{ 0.f, 1.f };
			m_Direction = Direction::up;
		}
		else if(!(isHittingDown || isHittingDown_2))
		{
			m_Position.x += m_Width / 2;
			m_Position.y -= m_Height / 2 - 1;
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
			m_Position.y = hitinfo_right.intersectPoint.y;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		else if (isHittingRight_2)
		{
			m_Position.y = hitinfo_right_2.intersectPoint.y;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{

			m_Position.x -= m_Width / 2 - 1;
			m_Position.y -= m_Height / 2;
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
			m_Position.x = hitinfo_right.intersectPoint.x;
			m_Velocity = Vector2f{ 0.f, -1.f };
			m_Direction = Direction::down;
		}
		else if (isHittingRight_2)
		{
			m_Position.x = hitinfo_right_2.intersectPoint.x;
			m_Velocity = Vector2f{ 0.f, -1.f };
			m_Direction = Direction::down;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{
			m_Position.x -= m_Width / 2;
			m_Position.y += m_Height / 2 + 1;
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
			m_Position.y = hitinfo_right.intersectPoint.y - m_Height;
			m_Velocity = Vector2f{ -1.f, 0.f };
			m_Direction = Direction::left;
		}
		else if (isHittingRight_2)
		{
			m_Position.y = hitinfo_right_2.intersectPoint.y - m_Height;
			m_Velocity = Vector2f{ -1.f, 0.f };
			m_Direction = Direction::left;
		}
		else if (!(isHittingDown || isHittingDown_2))
		{
			m_Position.x += m_Width / 2 + 1;
			m_Position.y += m_Height / 2;
			m_Velocity = Vector2f{ 1.f, 0.f };
			m_Direction = Direction::right;
		}
		break;
	default:
		break;
	}
	
	m_Position.x += m_Velocity.x * m_Speed * elapsedSec;
	m_Position.y += m_Velocity.y * m_Speed * elapsedSec;

	m_Position.x = m_Position.x;
	m_Position.y = m_Position.y;
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
