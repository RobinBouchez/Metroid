#pragma once
#include "Effect.h"

class Texture;
class GameObject;
class Bullet;

class BulletEffect final : public Effect
{
public:
	BulletEffect();
	virtual ~BulletEffect() =  default;

	virtual void Draw() const override;
	void DrawEffect(const Point2f& pos) const;
	virtual void Update(float elapsedSec) override;

private:
	Texture* m_pTexture;

};

