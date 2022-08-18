#pragma once
#include "Screen.h"

class Texture;

class GameOverScreen final : public Screen
{
public:
	GameOverScreen(const Point2f& position);
	virtual ~GameOverScreen() = default;

	virtual void Draw() const override;

private:
	Texture* m_pTexture;

};

