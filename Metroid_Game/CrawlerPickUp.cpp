#include "pch.h"
#include "CrawlerPickUp.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Animation.h"

CrawlerPickUp::CrawlerPickUp(const Point2f& position)
	: PickUp{position}
	, m_pAnimation{}
	, m_Rows{ 5 }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("PickUp");
}


CrawlerPickUp::~CrawlerPickUp()
{
}

void CrawlerPickUp::Draw() const
{
	PickUp::Draw();

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

void CrawlerPickUp::Update(float elapsedSec)
{
	PickUp::Update(elapsedSec);
}
