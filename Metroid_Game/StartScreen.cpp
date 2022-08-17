#include "pch.h"
#include "StartScreen.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Animation.h"

StartScreen::StartScreen(const Point2f& position)
	: Screen(position)
	, m_pTexture{ nullptr }
	, m_AmountOfFrames{ 8 }
	, m_pAnimation{new Animation(m_AmountOfFrames, 0.2f)}
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("StartScreen");

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
	srcRect.width = m_Boundaries.width;
	srcRect.height = m_Boundaries.height;


	if (m_pAnimation->m_AnimationFrame >= m_AmountOfFrames)
	{
		srcRect.left = m_pTexture->GetWidth() - m_pTexture->GetWidth() / m_AmountOfFrames;
	}

	float scale = 3.35f;
	glPushMatrix();
		glScalef(scale, scale, 0);
		m_pTexture->Draw(m_Boundaries, srcRect);
	glPopMatrix();
}

void StartScreen::Update(float elapsedSec)
{
	m_pAnimation->Update(elapsedSec);
}