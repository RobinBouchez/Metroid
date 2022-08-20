#include "pch.h"
#include "BulletEffect.h"
#include "Bullet.h"
#include "Texture.h"
#include "TextureManager.h"
#include "utils.h"

BulletEffect::BulletEffect() : Effect()
	, m_pTexture{ nullptr }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("BulletEffect");
}

void BulletEffect::Draw() const
{
	m_pTexture->Draw();
}

void BulletEffect::Update(float elapsedSec)
{
	Effect::Update(elapsedSec);
}

bool BulletEffect::Trigger(Bullet* bullet, GameObject* object)
{
	if (utils::IsOverlapping(bullet->GetBoundaries(), object->GetBounds()))
	{
		return true;
	}
}
