#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"

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
	for (auto& e : m_pEnemies)
	{
		e->Update(elapsedSec);
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