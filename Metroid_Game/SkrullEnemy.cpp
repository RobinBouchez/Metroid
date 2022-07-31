#include "pch.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"

SkrullEnemy::SkrullEnemy(const Point2f& position)
	: Enemy(position)
{
	CalculateTexture("Skrull", 3);
}

SkrullEnemy::~SkrullEnemy()
{
}

void SkrullEnemy::Draw() const
{
	Enemy::Draw();
}

void SkrullEnemy::Update(float elapsedSec, World* level)
{
	Enemy::Update(elapsedSec);
}
