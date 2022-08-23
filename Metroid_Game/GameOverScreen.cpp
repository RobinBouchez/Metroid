#include "pch.h"
#include "GameOverScreen.h"
#include "Texture.h"
#include "TextureManager.h"
#include "SoundManager.h"

GameOverScreen::GameOverScreen(const Point2f& position, const Window& window) : Screen(position, window)
	, m_pTexture{ nullptr }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("GameOver");
	SoundManager::GetInstance().CreateSound("Dead");
	SoundManager::GetInstance().Play("Dead");

}

void GameOverScreen::Draw() const
{
	float scale = 3.35f;
	glPushMatrix();
	glScalef(scale, scale, 0);

	m_pTexture->Draw(m_ScreenPos);
	glPopMatrix();	
}

void GameOverScreen::Update(float elapsedSec)
{
}
