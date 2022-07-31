#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Bullet.h"
#include "Animation.h"

Bullet::Bullet()
	: m_Rows{4}
	, m_pAnimation{ new Animation(m_Rows) }
	, m_Position{ 2000 , 200}
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("Bullet");
}

Bullet::~Bullet()
{
	delete m_pAnimation;
	m_pAnimation;
}

void Bullet::Draw() const
{
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
	m_pAnimation->Update(elapsedSec);
}
