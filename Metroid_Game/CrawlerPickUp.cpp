#include "pch.h"
#include "CrawlerPickUp.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Animation.h"

CrawlerPickUp::CrawlerPickUp(const Point2f& position)
	: PickUp{position}
	, m_pAnimation{ new Animation(4)}
	, m_Columns{ 5 }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("PickUp");
	m_Position.x = position.x;
	m_Position.y = position.y;
	m_Width = 30.f;
	m_Height = 30.f;
}


CrawlerPickUp::~CrawlerPickUp()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void CrawlerPickUp::Draw() const
{
	if (!m_IsActive)
	{
		return;
	}

	if (m_pAnimation == nullptr)
	{
		return;
	}
	Rectf m_SourceClip;

	m_SourceClip.left = m_pAnimation->m_AnimationFrame * 29.f;
	m_SourceClip.bottom = m_pTexture->GetHeight();
	m_SourceClip.height = m_pTexture->GetHeight();
	m_SourceClip.width = 29.f;

	m_pTexture->Draw(GetBoundaries(), m_SourceClip);

}

void CrawlerPickUp::Update(float elapsedSec)
{
	PickUp::Update(elapsedSec);
	m_pAnimation->Update(elapsedSec);
}
