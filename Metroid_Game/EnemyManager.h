#pragma once
#include <vector>

class World;
class Enemy;
class Player;
class BulletManager;
class EffectManager;

class EnemyManager final
{
public:
	EnemyManager() = default;
	~EnemyManager();
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

	void Draw() const;
	void Update(float elapsedSec, const Player* avatar, const World* level);
	void AddEnemy(Enemy* newEnemy);

	void SetBulletManagerPointer(BulletManager* bulletManager);

	void Clear();
private:
	std::vector<Enemy*> m_pEnemies;
	BulletManager* m_pBulletManager;
};

