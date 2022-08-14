#pragma once
#include "Vector2f.h"
class Texture;
class Animation;

class Bullet
{
public:

	Bullet(const Point2f& pos, const Vector2f& velocity);
	virtual ~Bullet();

	void Draw() const;
	void Update(float elapsedSec);
	Rectf GetBoundaries() const;

	Point2f m_Position;

	bool GetIsActive() const;
	void SetIsActive(bool value);

private:
	Vector2f m_Velocity;
	Animation* m_pAnimation;
	Texture* m_pTexture;

	const float m_Speed;
	const int m_Rows;

	bool m_IsActive;

	Rectf m_Boundaries;
};

