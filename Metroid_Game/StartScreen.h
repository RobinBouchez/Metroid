#pragma once
#include "Screen.h"

class Texture;
class Animation;

class StartScreen : public Screen
{
public:
	StartScreen(const Point2f& position);
	virtual ~StartScreen();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:
	Texture* m_pTexture;
	Texture* m_pEndTexture;
	Animation* m_pAnimation;

	const int m_AmountOfFrames;

};

