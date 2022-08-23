#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Bullet.h"
#include "Animation.h"
#include "utils.h"
#include "BulletEffect.h"

Bullet::Bullet(const Point2f& pos, const Vector2f& velocity)
	: m_Rows{ 2 }
	, m_pAnimation{ new Animation(m_Rows) }
	, m_Speed{ 300  }
	, m_LifeTime{}
	, m_Hit{ false }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("bullet");

	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Width = m_pTexture->GetWidth() / m_Rows;
	m_Height = m_pTexture->GetHeight();

	m_Velocity = velocity;

	m_pBulletEffect = new BulletEffect();
}

Bullet::~Bullet()
{
	delete m_pAnimation;
	m_pAnimation;

	delete m_pBulletEffect;
	m_pBulletEffect = nullptr;
}

void Bullet::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}

	if (m_Hit)
	{
		m_pBulletEffect->DrawEffect(m_Position);
	}
	else
	{
		Rectf m_SourceClip;
		Rectf m_TextureClip;

		m_SourceClip.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Rows;
		m_SourceClip.bottom = m_pTexture->GetHeight();
		m_SourceClip.height = m_pTexture->GetHeight();
		m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;


		m_TextureClip.left = m_Position.x;
		m_TextureClip.bottom = m_Position.y;
		m_TextureClip.height = m_pTexture->GetHeight();
		m_TextureClip.width = m_pTexture->GetWidth() / m_Rows;

		m_pTexture->Draw(m_TextureClip, m_SourceClip);
	}
}

void Bullet::Update(float elapsedSec)
{
	if (!m_IsActive)
	{
		return;
	}

	m_pAnimation->Update(elapsedSec);

	Vector2f v = m_Velocity * m_Speed; 

	if (m_Hit)
	{
		m_pBulletEffect->Update(elapsedSec);
	}
	else
	{
		m_Position.x += v.x * elapsedSec;
		m_Position.y += v.y * elapsedSec;
	}

	m_LifeTime += elapsedSec;

	if (m_LifeTime >= 1.f)
	{
		m_IsActive = false;
	}

}

void Bullet::Explode()
{
	m_Hit = true;
}