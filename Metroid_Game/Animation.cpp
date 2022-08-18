#include "pch.h"
#include "Animation.h"

Animation::Animation(const int& frameCount, const float& speed)
	: m_AnimationSpeed{ speed }
	, m_AnimationTime{}
	, m_AnimationFrame{}
	, m_AnimationFrameCount{ frameCount }
{
}

void Animation::Update(float elapsedSec)
{
	m_AnimationTime += elapsedSec;

	if (m_AnimationTime >= m_AnimationSpeed)
	{
		m_AnimationFrame++;
		m_AnimationFrame %= m_AnimationFrameCount;
		m_AnimationTime = 0;
	}
}
//
//Animation* Animation::Create(const int& frameCount, const float& speed)
//{
//}
//
