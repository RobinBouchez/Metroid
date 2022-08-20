#pragma once
#include "Screen.h"

class Texture;

class GameOverScreen final : public Screen
{
public:
	GameOverScreen(const Point2f& position, const Window& window);
	virtual ~GameOverScreen() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:
	Texture* m_pTexture;

};

