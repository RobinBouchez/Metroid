#pragma once
#include <vector>
#include "Manager.h"

class Enemy;
class World;
class Player;

class EnemyManager final : public Manager<EnemyManager>
{
public:
	EnemyManager() = default;
	~EnemyManager() = default;
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

	void Add(Enemy* enemy);
	std::vector<Enemy*> GetEnemies();
	void Draw() const;
	void Update(float elapsedSec, World* level, Player* player);
	void Cleanup();

	friend std::ostream& operator<<(std::ostream& os, const EnemyManager& em);
	friend std::istream& operator>>(std::istream& os, const EnemyManager& em);

private:
	std::vector<Enemy*> m_pEnemies;
};

