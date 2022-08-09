#include "pch.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Texture.h"
#include "World.h"
#include "Animation.h"

Enemy::Enemy(const Point2f& position)
	: m_Position{ position }
	, m_State{ State::alive }
	, m_Boundaries{}
	, m_HorizontalSpeed{ 180.f }
	, m_Health{ 100 }
	, m_Damage{ 25 }
	, m_pAnimation{ new Animation( 2 )}
	, m_Columns{3}
	, m_pTexture{nullptr}
	, m_pWorld{ new World(1,1)}
	, m_IsActive{}
	, m_CurrentHealth{}
{
}

Enemy::~Enemy()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;
}

void Enemy::Update(float ElapsedSec)
{
	if (!m_IsActive)
	{
		return;
	}
	m_pAnimation->Update(ElapsedSec);
}

void Enemy::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}

	m_pTexture->Draw(m_Position, Rectf{ m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Columns, 0,
										m_pTexture->GetWidth() / 3, m_pTexture->GetHeight() });
}

void Enemy::CalculateTexture(const std::string& filename, const int columns)
{
	m_pTexture = TextureManager::GetInstance().CreateTexture(filename);

	m_Columns = columns;

	m_Boundaries.left = m_Position.x;
	m_Boundaries.bottom = m_Position.y;
	m_Boundaries.width = m_pTexture->GetWidth() / columns;
	m_Boundaries.height = m_pTexture->GetHeight();
}

Rectf Enemy::GetBoundaries() const
{
	return m_Boundaries;
}

void Enemy::TakeHit()
{
	m_CurrentHealth--;
	if (m_CurrentHealth <= 0)
	{
		m_IsActive = false;
	}
}
