#pragma once
#include "Texture.h"
#include <vector>
#include "Vector2f.h"

class World
{
public:
	World(const float LevelHeight, const float Levelwidth);
	~World();

	void Draw() const;

	float GetWidth() const;
	float GetHeight() const;
	float GetX() const;
	float GetY() const;
	Point2f GetLastShapePosition();

	float GetRatio();
	void HandleCollision(Rectf& shape, Vector2f& velocity);
	bool IsOnGround(const Rectf& actorShape);

	const std::vector<std::vector<Point2f>>& GetVertices() const;

private:
	std::vector<std::vector<Point2f>> m_Vertices;
	Texture* m_WorldTexture;
	const Point2f m_TexturePosition;

	const float m_TextureWidth, m_TextureHeight;

	void LoadSVG();
	
	Point2f m_LastShapePosition;
};

