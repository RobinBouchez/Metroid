#include "pch.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Texture.h"
#include "World.h"
#include "Animation.h"
#include "utils.h"
#include "HUD.h"
#include "Vitals.h"
#include "Component.h"

Enemy::Enemy(const Point2f& position)
	: m_Position{ position }
	, m_CurrentHealth{}
	, m_Vitals{ new Vitals(m_CurrentHealth) }
	, m_Boundaries{}
	, m_HorizontalSpeed{ 180.f }
	, m_pAnimation{ new Animation(2)}
	, m_Columns{3}
	, m_pTexture{ nullptr }
	, m_IsActive{ true }
{
}

Enemy::~Enemy()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_Vitals;
	m_Vitals = nullptr;
}

void Enemy::Update(float elapsedSec, World* level, Player* player)
{
	if (!m_IsActive)
	{
		return;
	}
	m_pAnimation->Update(elapsedSec);
}

void Enemy::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}

	m_pTexture->Draw(m_Boundaries, Rectf{ m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Columns, 0,
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

bool Enemy::GetIsActive() const
{
	return m_IsActive;
}

Rectf Enemy::GetBoundaries() const
{
	return m_Boundaries;
}

void Enemy::TakeHit()
{
	m_Vitals->SetHealth(m_CurrentHealth--);
	if (m_Vitals->GetHealth() <= 0)
	{
		m_IsActive = false;

		HUD::GetInstance().UpdateScore(3);
	}

}
