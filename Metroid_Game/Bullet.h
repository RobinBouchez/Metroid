#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
class BulletEffect;
class Animation;

class Bullet final : public GameObject
{
public:
	Bullet(const Point2f& pos, const Vector2f& velocity);
	virtual ~Bullet();

	void Draw() const;
	void Update(float elapsedSec);

	void Explode();

private:
	Animation* m_pAnimation;
	Texture* m_pTexture;
	BulletEffect* m_pBulletEffect;

	const float m_Speed;
	const int m_Rows;

	float m_LifeTime;

	bool m_Hit;
};

