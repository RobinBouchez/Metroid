#include "pch.h"
#include "Level.h"
#include "SVGParser.h"
#include "utils.h"
#include "Player.h"
#include "GameObject.h"
#include "BulletManager.h"
#include "utils.h"
#include "Bullet.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Camera.h"
#include "structs.h"
#include "game.h"

Level::Level(const int index)
	: m_LevelTexture{nullptr}
	, m_TexturePosition{ 0, 0 }
	, m_TextureWidth{}
	, m_TextureHeight{}
	, m_Vertices{}
	, m_Index{index} 
	, m_Scale{}
{
	m_LevelTexture = TextureManager::GetInstance().CreateTexture("Level" + std::to_string(index));

	const_cast<float&>(m_TextureWidth) = m_LevelTexture->GetWidth();
	const_cast<float&>(m_TextureHeight) = m_LevelTexture->GetHeight();

	LoadSVG();

	m_Scale = Game::m_Window.height / m_TextureHeight;

	CreateCamera(Game::m_Window.width, Game::m_Window.height, m_Scale);
}

Level::~Level()
{
	delete m_pCamera;
	m_pCamera = nullptr;
}

void Level::Draw() const
{
	//glPushMatrix();
	//glScalef(m_Scale, m_Scale, 0);
	m_LevelTexture->Draw(Rectf{ m_TexturePosition.x, m_TexturePosition.y, m_TextureWidth, m_TextureHeight });
	//glPopMatrix();
}

void Level::Update(float elapsedSec)
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

Rectf Level::GetBounds() const
{ 
	return Rectf{ m_TexturePosition.x, m_TexturePosition.y, m_TextureWidth, m_TextureHeight };
}

int Level::GetIndex() const
{
	return m_Index;
}

Point2f Level::GetLastShapePosition()
{
	return Point2f(m_LastShapePosition.x, m_LastShapePosition.y);
}


void Level::LoadSVG()
{
	SVGParser::GetVerticesFromSvgFile("Resources/Levelsvg" + std::to_string(m_Index) + ".svg", m_Vertices);
}

void Level::CreateCamera(const float width, const float height, const float scale)
{
	m_pCamera = new Camera(width, height, scale);
	m_pCamera->SetLevelBoundaries(Level::GetBounds());
}

void Level::HandleCollision(Rectf& shape, Vector2f& actorVelocity)
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

bool Level::IsOnGround(const Rectf& actorShape)
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

const std::vector<std::vector<Point2f>>& Level::GetVertices() const
{
	return m_Vertices;
}


