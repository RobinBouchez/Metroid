#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "utils.h"
#include "Bullet.h"

void EnemyManager::Add(Enemy* enemy)
{
	m_pEnemies.push_back(enemy);
}

void EnemyManager::Draw() const
{
	for (auto& e : m_pEnemies)
	{
		e->Draw();
	}
}

void EnemyManager::Update(float elapsedSec)
{
	auto& bullets = BulletManager::GetInstance().GetBullets();
	for (auto& e : m_pEnemies)
	{
		e->Update(elapsedSec);
		for (auto &b: bullets)
		{
			if (utils::IsOverlapping(b->GetBoundaries(), e->GetBoundaries()))
			{
				//enemy health
				e->TakeHit();
			}
		}
	}

}

void EnemyManager::Cleanup()
{
	for (auto& e : m_pEnemies)
	{
		delete e;
		e = nullptr;
	}
	m_pEnemies.clear();
}