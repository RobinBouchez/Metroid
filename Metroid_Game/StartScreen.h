#pragma once
#include "Screen.h"

class Texture;
class Animation;

class StartScreen final : public Screen
{
public:
	StartScreen(const Point2f& position);
	virtual ~StartScreen();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:

	virtual void Continue(bool value) override;

	Texture* m_pTexture;
	Texture* m_pEndTexture;
	Animation* m_pAnimation;

	const int m_AmountOfFrames;

	bool m_Continue;

};

