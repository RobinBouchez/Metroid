#include "pch.h"
#include "Player.h"
#include "Animation.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Morphball.h"
#include "utils.h"
#include "SoundManager.h"
#include "SoundEffect.h"

bool Morphball::m_IsHit = false;

Morphball::Morphball()
	: m_Position{ 1136.f, 250.f }
	, m_Rows{ 4 }
	, m_pAnimation{ new Animation(m_Rows, 0.05f )}
	, m_DstRect{}
	, m_SrcRect{}
	//, m_pSound{}//SoundManager::GetInstance().CreateSound("morphball")}
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("Morphball");
}

Morphball::~Morphball()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void Morphball::Draw() const
{
	if (!m_IsHit)
	{
		m_pTexture->Draw(m_DstRect, m_SrcRect);
	}
}

void Morphball::Update(float elapsedSec)
{
	ChangeColor();

	m_pAnimation->Update(elapsedSec);
}

bool Morphball::CheckIfhit(Player* player)
{
	Point2f playerPos{ player->m_Shape.left, player->m_Shape.bottom };
	if (playerPos.x >= m_DstRect.left && playerPos.x <= m_DstRect.left + m_DstRect.width)
	{
		if (playerPos.y >= m_DstRect.bottom && playerPos.y <= m_DstRect.bottom + m_DstRect.height)
		{
			if (!m_IsHit)
			{
				SoundManager::GetInstance().Play("PickUp");
			}

			m_IsHit = true;
			return true;		
		}
	}
	return false;
}

void Morphball::ChangeColor()
{
	if (!m_IsHit)
	{
		m_SrcRect.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Rows;
		m_SrcRect.bottom = 0.f;
		m_SrcRect.width = m_pTexture->GetWidth() / m_Rows;
		m_SrcRect.height = m_pTexture->GetHeight();
	}
	else
	{
		m_SrcRect.left = 0.f;
		m_SrcRect.bottom = 0.f;
		m_SrcRect.width = m_pTexture->GetWidth() / m_Rows;
		m_SrcRect.height = m_pTexture->GetHeight();
	}

	m_DstRect.left = m_Position.x;
	m_DstRect.bottom = m_Position.y;
	m_DstRect.width = m_pTexture->GetWidth() / m_Rows;
	m_DstRect.height = m_pTexture->GetHeight();
}
