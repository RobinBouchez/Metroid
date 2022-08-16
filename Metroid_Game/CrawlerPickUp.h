#pragma once
#include "PickUp.h"
class Texture;
class Animation;

class CrawlerPickUp : public PickUp
{
public:
	CrawlerPickUp(const Point2f& position);
	virtual ~CrawlerPickUp();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:
	Texture* m_pTexture;
	Animation* m_pAnimation;

	const int m_Rows;

};

