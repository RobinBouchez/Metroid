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
#include "PickUpManager.h"
#include "PickUp.h"
#include "CrawlerPickUp.h"
#include "Bullet.h"
#include "BulletManager.h"

Enemy::Enemy(const Point2f& position)
	: m_CurrentHealth{ 3 }
	, m_Vitals{ nullptr }
	, m_HorizontalSpeed{ 180.f }
	, m_pAnimation{ new Animation(2)}
	, m_Columns{3}
	, m_pTexture{ nullptr }
{
	m_Position = position;

	m_Vitals = new Vitals(m_CurrentHealth);
	m_Tag = "Enemy";
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

	m_pTexture->Draw(GetBoundaries(), Rectf{m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Columns, 0,
										m_pTexture->GetWidth() / 3, m_pTexture->GetHeight() });
}

void Enemy::CalculateTexture(const std::string& filename, const int columns)
{
	m_pTexture = TextureManager::GetInstance().CreateTexture(filename);

	m_Columns = columns;

	m_Width = m_pTexture->GetWidth() / columns;
	m_Height = m_pTexture->GetHeight();
}

std::string Enemy::GetTag() const
{
	return m_Tag;
}

void Enemy::SpawnPickup()
{
	if (rand() % 10 <= 7) // Spawn Pickup with a 70% chance
	{
		PickUpManager::GetInstance().Create(new CrawlerPickUp(Point2f{m_Position.x, m_Position.y}));
	}
}

void Enemy::TakeHit()
{
	m_Vitals->SetHealth(--m_CurrentHealth);
	if (m_Vitals->GetHealth() <= 0)
	{
		m_IsActive = false;
		SpawnPickup();

		HUD::GetInstance().UpdateScore(3);
		BulletManager::GetInstance().GetBullets().back()->Explode();
	}
}
