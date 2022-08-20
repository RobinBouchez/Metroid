#include "pch.h"
#include "StartScreen.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Animation.h"

StartScreen::StartScreen(const Point2f& position, const Window& window)
	: Screen(position, window)
	, m_pTexture{ nullptr }
	, m_AmountOfFrames{ 8 }
	, m_pAnimation{new Animation(m_AmountOfFrames, 0.2f)}
	, m_Continue{false}
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("StartScreen");
	m_pEndTexture = TextureManager::GetInstance().CreateTexture("StartScreen_end");

	m_Boundaries.width = m_pTexture->GetWidth() / m_AmountOfFrames;
	m_Boundaries.height = m_pTexture->GetHeight();
	m_Boundaries.left = position.x;
	m_Boundaries.bottom = position.y;
}

StartScreen::~StartScreen()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void StartScreen::Draw() const
{
	Rectf srcRect;

	srcRect.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_AmountOfFrames;
	srcRect.bottom = 0.f;
	srcRect.width = GetBoundaries().width;
	srcRect.height = GetBoundaries().height;


	
	if (m_pAnimation->m_AnimationFrame >= m_AmountOfFrames && !m_Continue)
	{
		srcRect.left = m_pTexture->GetWidth() - m_pTexture->GetWidth() / m_AmountOfFrames;
	}

	float scale = 3.35f;
	glPushMatrix();
		glScalef(scale, scale, 0);
		if (!m_Continue)
		{
			m_pTexture->Draw(m_Boundaries, srcRect);
		}
		else if(m_Continue)
		{
			m_pEndTexture->Draw(m_Boundaries, srcRect);
		}
	glPopMatrix();
}

void StartScreen::Update(float elapsedSec)
{
	m_pAnimation->Update(elapsedSec);

	if (m_pAnimation->m_AnimationFrame >= m_AmountOfFrames)
	{
		m_HasPlayed = true;
	}
}

void StartScreen::Continue(bool value)
{
	Screen::Continue(value);
}
