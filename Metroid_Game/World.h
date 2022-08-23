#pragma once
#include "Vector2f.h"
#include "LevelManager.h"
#include <vector>

class World final : public LevelManager
{
public:
	World();
	~World();

	void Draw() const;
	void Update(float elapsedSec);
	void CleanUp();

	Level* GetLevel() const;

	Point2f GetLastShapePosition();

	void HandleCollision(Rectf& shape, Vector2f& velocity);
	bool IsOnGround(const Rectf& actorShape);

	const std::vector<std::vector<Point2f>>& GetVertices() const;

	void SaveEnemies();
	void LoadEnemies();

	int m_LevelIndex{0};
};

