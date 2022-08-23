#include "pch.h"
#include "Door.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Player.h"
#include "utils.h"
#include "Animation.h"

Door::Door(const Point2f& position) : GameObject()
	, m_pTexture{ nullptr }
	, m_IsClosed{ true }
{
	m_Position = position;
	m_pTexture = TextureManager::GetInstance().CreateTexture("Door");
	m_Width = m_pTexture->GetWidth() / 3.f; 
	m_Height = m_pTexture->GetHeight();
}

Door::~Door()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;
}

void Door::Draw() const
{
	if (m_IsClosed)
	{
		Rectf destRect;
		destRect.left = m_Position.x;
		destRect.bottom = m_Position.y;
		destRect.width = m_Width;
		destRect.height = m_Height;

		Rectf srcRect;
		srcRect.left = m_pAnimation->m_AnimationFrame * m_Width;
		srcRect.bottom = 0.f;
		srcRect.width = m_Width;
		srcRect.height = m_Height;

		m_pTexture->Draw(destRect, srcRect);
	}
}

void Door::Update(float elapsedSec)
{
	if (utils::IsOverlapping(m_pPlayer->m_Shape, this->GetBoundaries()))
	{
		if (!m_IsClosed)
		{
			m_pCamera->Transition(); // to next level
			Open();
		}
	}
}

bool Door::Open()
{
	m_IsClosed = false;
	return m_IsClosed;
}
