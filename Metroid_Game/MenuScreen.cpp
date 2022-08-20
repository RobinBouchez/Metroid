#include "pch.h"
#include "MenuScreen.h"
#include "Texture.h"
#include "TextureManager.h"

MenuScreen::MenuScreen(const Point2f& position, const Window& window) : Screen(position, window)
	, m_pTexture{ nullptr }
	, m_pButtonTexture{ nullptr }
	, m_Option{ Option::Start }
	, m_ButtonPos{ 0.f, 0.f }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("menu");
	m_pButtonTexture = TextureManager::GetInstance().CreateTexture("menuButton");
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Draw() const
{
	m_pTexture->Draw(m_ScreenPos);

	switch (m_Option)
	{
	case MenuScreen::Option::Start:
		m_pButtonTexture->Draw(m_ButtonPos);
		break;
	case MenuScreen::Option::Continue:
		m_pButtonTexture->Draw(m_ButtonPos);
		break;
	}

}

void MenuScreen::Update(float elapsedSec)
{
	switch (m_Option)
	{
	case MenuScreen::Option::Start:
		m_ButtonPos.y = 0;
		break;
	case MenuScreen::Option::Continue:
		m_ButtonPos.y = 0;
		break;
	}
}

