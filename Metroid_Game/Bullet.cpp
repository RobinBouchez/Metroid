#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Bullet.h"
#include "Animation.h"
#include "utils.h"

Bullet::Bullet(const Point2f& pos, const Vector2f& velocity)
	: m_Rows{4}
	, m_pAnimation{ new Animation(m_Rows) }
	, m_Position{ pos }
	, m_Velocity{ velocity }
	, m_Speed{ 200 }
	, m_IsActive{ true }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("Bullet");

	m_Boundaries.left = pos.x;
	m_Boundaries.bottom = pos.y;
	m_Boundaries.width = m_pTexture->GetWidth() / m_Rows;
	m_Boundaries.height = m_pTexture->GetHeight();
}

Bullet::~Bullet()
{
	delete m_pAnimation;
	m_pAnimation;
}

void Bullet::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}
	Rectf m_SourceClip;
	Rectf m_TextureClip;

	m_SourceClip.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Rows;
	m_SourceClip.bottom = m_pTexture->GetHeight();
	m_SourceClip.height = m_pTexture->GetHeight();
	m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;


	m_TextureClip.left =  m_Position.x;
	m_TextureClip.bottom = m_Position.y;
	m_TextureClip.height = m_pTexture->GetHeight();
	m_TextureClip.width = m_pTexture->GetWidth() / m_Rows;

	m_pTexture->Draw(m_TextureClip, m_SourceClip);
}

void Bullet::Update(float elapsedSec)
{
	if (!m_IsActive)
	{
		return;
	}

	m_pAnimation->Update(elapsedSec);

	Vector2f v = m_Velocity * m_Speed; 

	m_Position.x += v.x * elapsedSec;
	m_Position.y += v.y * elapsedSec;

	m_Boundaries.left = m_Position.x;
	m_Boundaries.bottom = m_Position.y;
}

Rectf Bullet::GetBoundaries() const
{
	return m_Boundaries;
}

bool Bullet::GetIsActive() const
{
	return m_IsActive;
}

void Bullet::SetIsActive(bool value)
{
	m_IsActive = value;
}


