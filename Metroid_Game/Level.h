#pragma once
#include "Vector2f.h"

#include <vector>

class Texture;

class Level final
{
public:
	Level(const int& index);
	~Level() = default;

	void Draw() const;
	void Update(float elapsedSec);

	Rectf GetBounds() const;


	void HandleCollision(Rectf& shape, Vector2f& velocity);
	bool IsOnGround(const Rectf& actorShape);

	const std::vector<std::vector<Point2f>>& GetVertices() const;
	Point2f GetLastShapePosition();

protected:
	void LoadSVG();

private:
	std::vector<std::vector<Point2f>> m_Vertices;
	Texture* m_LevelTexture;
	const Point2f m_TexturePosition;
	const float m_TextureWidth, m_TextureHeight;
	Point2f m_LastShapePosition;

	const int m_Index;
};

