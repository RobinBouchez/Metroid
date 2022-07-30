#include "pch.h"
#include "EnemyManager.h"
#include <algorithm>
#include "Enemy.h"
#include <set>
#include "Player.h"
#include "BulletManager.h"

EnemyManager::~EnemyManager()
{
	Clear();
}

void EnemyManager::Draw() const
{
	for (Enemy* enemy : m_pEnemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::Update(float elapsedSec, const Player* avatar, const World* level)
{
	//std::vector<Enemy*>::iterator it;

	//for (Enemy* enemy : m_pEnemies)
	//{
	//	if (!enemy->GetIsImmobile())
	//	{
	//		enemy->Update(elapsedSec, m_pBulletManager, avatar, level);
	//	}
	//}
	//it = std::remove_if(m_pEnemies.begin(), m_pEnemies.end(), (Enemy* p)
	//	{
	//		if (p->InteractionsHealthBar().GetHP() <= 0)
	//		{
	//			delete p;
	//			p = nullptr;
	//			return true;
	//		}
	//		return false;
	//	});
	//m_pEnemies.erase(it, m_pEnemies.end());
}

void EnemyManager::AddEnemy(Enemy* newEnemy)
{
	m_pEnemies.push_back(newEnemy);
}

void EnemyManager::SetBulletManagerPointer(BulletManager* bulletManager)
{
	m_pBulletManager = bulletManager;
}

void EnemyManager::Clear()
{
	for (Enemy* enemy : m_pEnemies)
	{
		delete enemy;
		enemy = nullptr;
	}
	m_pEnemies.clear();
}