#include "pch.h"
#include "MenuScreen.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ScreenManager.h"

bool MenuScreen::m_SaveGame = false;

MenuScreen::MenuScreen(const Point2f& position, const Window& window) : Screen(position, window)
	, m_pTexture{ nullptr }
	, m_pButtonTexture{ nullptr }
	, m_Option{ Option::Start }
	, m_ButtonPos{ 145.f, 0.f }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("Menu");
	m_pButtonTexture = TextureManager::GetInstance().CreateTexture("Button");
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Draw() const
{
	float scale = 3.35f;
	glPushMatrix();
		glScalef(scale, scale, 0);

		m_pTexture->Draw(m_ScreenPos);
		m_pButtonTexture->Draw(m_ButtonPos);
	glPopMatrix();
}

void MenuScreen::Update(float elapsedSec)
{
	const UINT8* State = SDL_GetKeyboardState(NULL);
	if (State[SDL_SCANCODE_UP])
	{
		m_Option = MenuScreen::Option::Start;
		m_SaveGame = false;
	}
	else if (State[SDL_SCANCODE_DOWN])
	{
		m_Option = MenuScreen::Option::Continue;
		m_SaveGame = true;
	}
	else if (State[SDL_SCANCODE_RETURN])
	{
		ScreenManager::GetInstance().GetCurrent()->SetIsActive(false);
	}


	switch (m_Option)
	{
	case MenuScreen::Option::Start:
		m_ButtonPos.y = 127.f;
		break;
	case MenuScreen::Option::Continue:
		m_ButtonPos.y = 103.f;
		break;
	}
}

