#include "pch.h"
#include "BulletManager.h"
#include "Bullet.h"

void BulletManager::Draw() const
{
	for (auto e : m_BulletVector)
	{
		e->Draw();
	}
}

void BulletManager::Create(Bullet* bullet)
{
	m_BulletVector.push_back(bullet);
}

void BulletManager::Update(float elapsedSec)
{
	for (auto e : m_BulletVector)
	{
		e->Update(elapsedSec);
	}
}

void BulletManager::Cleanup()
{ 
	for (auto e : m_BulletVector)
	{
		delete e;
		e = nullptr;
	}
	m_BulletVector.clear();
}

std::vector<Bullet*>& BulletManager::GetBullets()
{
	return m_BulletVector;
}
