#pragma once
#include "Vector2f.h"
#include "LevelManager.h"
#include <vector>

class World final : LevelManager
{
public:
	World();
	~World() = default;

	void Draw() const;
	void Update(float elapsedSec);
	void CleanUp();

	Level* GetLevel() const;


	Point2f GetLastShapePosition();

	void HandleCollision(Rectf& shape, Vector2f& velocity);
	bool IsOnGround(const Rectf& actorShape);

	const std::vector<std::vector<Point2f>>& GetVertices() const;
};

