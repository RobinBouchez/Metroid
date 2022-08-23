#include "pch.h"
#include "Door.h"
#include "Texture.h"
#include "TextureManager.h"

Door::Door() : GameObject()
	, m_pTexture{ nullptr }
	, m_IsClosed{ true }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("Door");
}

void Door::Draw() const
{
	m_pTexture->Draw();
}

void Door::Update(float elapsedSec)
{
}

bool Door::Open()
{
	return false;
}
