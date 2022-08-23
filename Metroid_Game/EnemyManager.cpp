#include "pch.h"
#include "EnemyManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "utils.h"
#include "Bullet.h"
#include "World.h"
#include "CrawlerEnemy.h"
#include "SkrullEnemy.h"
#include "Player.h"
#include "Vitals.h"


#include <iostream>

void EnemyManager::Add(Enemy* enemy)
{
	m_pEnemies.push_back(enemy);
}

std::vector<Enemy*> EnemyManager::GetEnemies()
{
	return m_pEnemies;
}

void EnemyManager::Draw() const
{
	for (auto& e : m_pEnemies)
	{
		e->Draw();
	}
}

void EnemyManager::Update(float elapsedSec, World* level, Player* player)
{
	auto& bullets = BulletManager::GetInstance().GetBullets();
	for (auto& e : m_pEnemies)
	{
		if (!e->GetIsActive())
		{
			continue;
		}
		e->Update(elapsedSec,level, player);
		for (auto &b: bullets)
		{
			if (b->GetIsActive())
			{
				if (utils::IsOverlapping(b->GetBoundaries(), e->GetBoundaries()))
				{
					//enemy health
					e->TakeHit();
				}
			}
		}
		if (utils::IsOverlapping(e->GetBoundaries(), player->m_Shape))
		{
			player->GetVitals()->TakeDamage(0.5f);
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

std::ostream& operator<<(std::ostream& os, const EnemyManager& em)
{
	for (int i = 0; i < em.m_pEnemies.size(); i++)
	{
		os << em.m_pEnemies[i]->GetTag();
		os << " ";
		os << em.m_pEnemies[i]->GetBoundaries().left;
		os << " ";
		os << em.m_pEnemies[i]->GetBoundaries().bottom;
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& os, const EnemyManager& em)
{
	while (!os.eof())
	{
		std::string tag{};
		os >> tag;

		std::string x{};
		os >> x;

		std::string y{};
		os >> y;
		
		if (tag == "Skrull")
		{
			em.GetInstance().Add(new SkrullEnemy(Point2f{ std::stof(x), std::stof(y) }));
		}
		else if (tag == "Crawler")
		{
			em.GetInstance().Add(new CrawlerEnemy(Point2f{ std::stof(x), std::stof(y) }));
		}
	}
	return os;
}
