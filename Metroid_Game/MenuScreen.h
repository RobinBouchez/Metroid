#pragma once
#include "Screen.h"

class Texture;

class MenuScreen final : public Screen
{
public:
	enum class Option { Start, Continue	};

	MenuScreen(const Point2f& position);
	virtual ~MenuScreen();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;


private:
	Texture* m_pTexture;
	Texture* m_pButtonTexture;

	Option m_Option;

	Point2f m_ButtonPos;
};

