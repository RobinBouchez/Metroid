#pragma once
#include "Manager.h"

class BulletManager final : public Manager<BulletManager>
{
public:
	~BulletManager() = default;	
    BulletManager(const BulletManager& other) = delete;
    BulletManager(BulletManager&& other) = delete;
    BulletManager& operator=(const BulletManager& other) = delete;
    BulletManager& operator=(BulletManager&& other) = delete;

private:
	BulletManager() = default;

};

