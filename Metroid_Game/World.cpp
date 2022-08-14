#include "pch.h"
#include "World.h"
#include "SVGParser.h"
#include "utils.h"
#include "Player.h"
#include "GameObject.h"
#include "BulletManager.h"
#include "utils.h"
#include "Bullet.h"

World::World(const float LevelHeight, const float Levelwidth)
	: m_WorldTexture{new Texture("Resources/Level.png")}
	, m_TexturePosition{ 0, 0 }
	, m_TextureWidth{ m_WorldTexture->GetWidth() }
	, m_TextureHeight{ m_WorldTexture->GetHeight() }
	, m_Vertices{}
{
	LoadSVG();
}

World::~World()
{
	delete m_WorldTexture;
	m_WorldTexture = nullptr;
}

void World::Draw() const
{
	m_WorldTexture->Draw(Rectf{ m_TexturePosition.x, m_TexturePosition.y, m_TextureWidth, m_TextureHeight });

	//DEBUG >>> SHOWS SVG OVERLAY <<<
	//for (int i = 0; i < m_Vertices.size(); i++)
	//{
	//	utils::DrawPolygon(m_Vertices[i]);
	//}
}

void World::Update(float elapsedSec)
{

	auto& bullets = BulletManager::GetInstance().GetBullets();
	for (auto& b : bullets)
	{
		Point2f rayPoint1 = Point2f{ b->GetBoundaries().left , b->GetBoundaries().bottom };
		Point2f rayPoint2 = Point2f{ b->GetBoundaries().left + b->GetBoundaries().width, b->GetBoundaries().bottom + b->GetBoundaries().height };
		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			utils::HitInfo hitInfo{};
			if (utils::Raycast(m_Vertices[i], rayPoint1, rayPoint2, hitInfo))
			{
				b->SetIsActive(false);
			}
		}
	}
}

float World::GetWidth() const
{
	return m_WorldTexture->GetWidth();
}

float World::GetHeight() const
{
	return m_WorldTexture->GetHeight();
}

float World::GetX() const
{
	return m_TexturePosition.x;
}

float World::GetY() const
{
	return m_TexturePosition.y;
}

Point2f World::GetLastShapePosition()
{
	return Point2f(m_LastShapePosition.x, m_LastShapePosition.y);
}

float World::GetRatio()
{
	float ratio;
	ratio = m_WorldTexture->GetWidth() / m_WorldTexture->GetHeight();
	return ratio;
}

void World::LoadSVG()
{
	SVGParser::GetVerticesFromSvgFile("Resources/levels.svg", m_Vertices);
}

void World::HandleCollision(Rectf& shape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo{};
	Point2f Center{ shape.left + shape.width / 2, shape.bottom + shape.height / 2 };
	Point2f RayPoint1{ shape.left + shape.width / 2, shape.bottom + shape.height };
	Point2f RayPoint2{ shape.left + shape.width / 2, shape.bottom };
	Point2f RayPoint3{ shape.left, shape.bottom + shape.height / 2 };
	Point2f RayPoint4{ shape.left + shape.width, shape.bottom + shape.height / 2 };

	bool isJumping = actorVelocity.y > 0;
	
	for (size_t i = 0; i < m_Vertices.size(); i++)
	{

		if (isJumping)
		{
			if (utils::Raycast(m_Vertices[i], Center, RayPoint1, hitInfo))
			{
				shape.bottom = hitInfo.intersectPoint.y - shape.height;
			}
		}
		else
		{
			if (utils::Raycast(m_Vertices[i], Center, RayPoint2, hitInfo))
			{
				shape.bottom = hitInfo.intersectPoint.y;
				actorVelocity.y = 0;
			}
		}

		if (utils::Raycast(m_Vertices[i], Center, RayPoint3, hitInfo))
		{
			shape.left = hitInfo.intersectPoint.x;
			
		}
		else if (utils::Raycast(m_Vertices[i], Center, RayPoint4, hitInfo))
		{
			shape.left = hitInfo.intersectPoint.x - shape.width;
		}
	}
}

bool World::IsOnGround(const Rectf& actorShape)
{
	utils::HitInfo hitInfo{};
	Point2f rayP1{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height * 0.5f };
	Point2f rayP2{ actorShape.left + actorShape.width / 2, actorShape.bottom };

	for (size_t i = 0; i < m_Vertices.size(); i++)
	{
		if (utils::Raycast(m_Vertices[i], rayP1, rayP2, hitInfo))
		{
			return true;
		}
	}
	return false;
}

const std::vector<std::vector<Point2f>>& World::GetVertices() const
{
	return m_Vertices;
}


