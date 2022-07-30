#include "pch.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"

SkrullEnemy::SkrullEnemy(Point2f& position)
	: Enemy(position)
	, m_Direction{}
{
}

SkrullEnemy::~SkrullEnemy()
{
	//delete m_pTexture;
}

void SkrullEnemy::Draw() const
{
}

void SkrullEnemy::Update(float elapsedSec, World* level)
{
}
