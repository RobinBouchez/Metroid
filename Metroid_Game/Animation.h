#pragma once
#include "Component.h"

class Animation final 
{
public:
	Animation() = default;
	Animation(const int& frameCount, const float& speed = 0.1f);
	virtual ~Animation() = default;

	virtual void Update(float elapsedSec);

	int m_AnimationFrame;

private:
	const float m_AnimationSpeed;
	float m_AnimationTime;

	const int m_AnimationFrameCount;
};

