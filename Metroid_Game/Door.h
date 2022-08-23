#pragma once
#include "GameObject.h"

class Texture;
class Animation;
class Camera;
class Player;

class Door final : public GameObject
{
public:
	Door(const Point2f& position);
	virtual ~Door();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool Open();

private:
	Texture* m_pTexture;
	Animation* m_pAnimation;
	Camera* m_pCamera;
	Player* m_pPlayer;

	bool m_IsClosed;
};

