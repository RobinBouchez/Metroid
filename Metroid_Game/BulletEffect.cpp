#include "pch.h"
#include "BulletEffect.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Texture.h"
#include "Animation.h"
#include "TextureManager.h"
#include "utils.h"

BulletEffect::BulletEffect() : Effect()
	, m_pTexture{ nullptr }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("BulletEffect");
	m_pAnimation = new Animation(3, 0.08f);
}

void BulletEffect::Draw() const
{

}

void BulletEffect::DrawEffect(const Point2f& pos) const
{
	float rows = 3;

	Rectf destRect{};
	destRect.left = pos.x;
	destRect.bottom = pos.y;
	destRect.width = m_pTexture->GetWidth() / rows;
	destRect.height = m_pTexture->GetHeight();

	Rectf srcRect{};
	srcRect.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / rows;
	srcRect.bottom = 0.f;
	srcRect.width = m_pTexture->GetWidth() / rows;
	srcRect.height = m_pTexture->GetHeight();
	m_pTexture->Draw(destRect, srcRect);
}

void BulletEffect::Update(float elapsedSec)
{
	m_pAnimation->Update(elapsedSec);
}

