#pragma once
#include "GameObject.h"

class Animation;

class Effect
{
public:
	Effect();
	virtual ~Effect();

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;

protected:
	Animation* m_pAnimation;

};

