#include "pch.h"
#include "SkrullEnemy.h"

SkrullEnemy::SkrullEnemy(Point2f& position)
	: Enemy(position)
	, m_Direction{}
{
}

SkrullEnemy::~SkrullEnemy()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void SkrullEnemy::Draw() const
{
}

void SkrullEnemy::Update(float elapsedSec, World* level)
{
}
