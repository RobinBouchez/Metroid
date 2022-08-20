#pragma once
#include "Effect.h"

class Texture;
class GameObject;

class BulletEffect final : public Effect
{
public:
	BulletEffect();
	virtual ~BulletEffect() =  default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool Trigger(Bullet* bullet, GameObject* object);

private:
	Texture* m_pTexture;
};

