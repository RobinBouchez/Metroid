#pragma once
#include "Manager.h"
#include <vector>

class Bullet;

class BulletManager final : public Manager<BulletManager>
{
public:
    BulletManager() = default;
	~BulletManager() = default;	
    BulletManager(const BulletManager& other) = delete;
    BulletManager(BulletManager&& other) = delete;
    BulletManager& operator=(const BulletManager& other) = delete;
    BulletManager& operator=(BulletManager&& other) = delete;

    void Draw() const;
    void Create(Bullet* bullet);
    void Update(float elapsedSec);
    void Cleanup();

    bool IsHit();

    std::vector<Bullet*>& GetBullets();

private:
    std::vector<Bullet*> m_BulletVector;
};

