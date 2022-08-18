#include "pch.h"
#include "Effect.h"
#include "Texture.h"
#include "TextureManager.h"

Effect::Effect(GameObject* object)
	: m_pTexture{ nullptr }
	, m_Object{ object }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("effects");
}

Effect::~Effect()
{
	delete m_Object;
	m_Object = nullptr;
}

void Effect::Draw() const
{
	m_pTexture->Draw(m_Object->GetPosition());
}

void Effect::Update(float elapsedSec)
{
}
