#include "pch.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Animation.h"

Enemy::Enemy(Point2f& position)
	: m_Position{ position }
	, m_pTexture{ new TextureManager() }
	, m_State{ State::alive }
	, m_Boundaries{}
	, m_HorizontalSpeed{ 180.f }
	, m_Health{ 100 }
	, m_Rows{ 3 }
	, m_Damage{ 25 }
	, m_pAnimation{ new Animation( 2 )}
{
	m_Boundaries.left = position.x;
	m_Boundaries.bottom = position.y;
	m_Boundaries.width = m_pTexture->GetWidth() / 3;
	m_Boundaries.height = m_pTexture->GetHeight();
	
}

Enemy::~Enemy()
{
	delete m_pTexture;
	m_pTexture = nullptr;

	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void Enemy::Update(float ElapsedSec)
{
	m_pAnimation->Update(ElapsedSec);
}

void Enemy::Draw() const
{
	m_pTexture->Draw(m_Position, Rectf{ m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Rows, 0,
												m_pTexture->GetWidth() / 3, m_pTexture->GetHeight() });
}