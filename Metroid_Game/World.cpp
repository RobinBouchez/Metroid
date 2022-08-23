#include "pch.h"
#include "World.h"
#include "Level.h"
#include "LevelManager.h"
#include "Camera.h"
#include "EnemyManager.h"

#include <iostream>
#include <fstream>

World::World()
{
	LevelManager::Add(new Level(m_LevelIndex));
}

World::~World()
{
}

void World::Draw() const
{
	LevelManager::GetCurrent()->Draw();
}

void World::Update(float elapsedSec)
{
	LevelManager::GetCurrent()->Update(elapsedSec);
}

void World::CleanUp()
{
	LevelManager::Cleanup();
}

Level* World::GetLevel() const
{
	return LevelManager::GetCurrent();
}

Point2f World::GetLastShapePosition()
{
	return LevelManager::GetCurrent()->GetLastShapePosition();
}

void World::HandleCollision(Rectf& shape, Vector2f& actorVelocity)
{
	LevelManager::GetCurrent()->HandleCollision(shape, actorVelocity);
}

bool World::IsOnGround(const Rectf& actorShape)
{
	return LevelManager::GetCurrent()->IsOnGround(actorShape);
}

const std::vector<std::vector<Point2f>>& World::GetVertices() const
{
	return LevelManager::GetCurrent()->GetVertices();
}

void World::SaveEnemies()
{
	std::string fileName = "Level" + std::to_string(LevelManager::GetCurrent()->GetIndex()) + ".txt";
	std::ofstream file(fileName);

	file << EnemyManager::GetInstance();

	file.close();
}

void World::LoadEnemies()
{
	std::string fileName = "Level" + std::to_string(LevelManager::GetCurrent()->GetIndex()) + ".txt";
	std::ifstream file(fileName);

	if (!EnemyManager::GetInstance().GetEnemies().empty())
	{
		EnemyManager::GetInstance().Cleanup();
	}

	file >> EnemyManager::GetInstance();

	file.close();
}
