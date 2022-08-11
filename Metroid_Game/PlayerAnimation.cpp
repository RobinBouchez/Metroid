#include "pch.h"
#include "PlayerAnimation.h"
#include "Player.h"

PlayerAnimation::PlayerAnimation(const int& frameCount, const float& speed)
	:Animation(frameCount, speed)
	, m_Player{nullptr}
{
}

PlayerAnimation::~PlayerAnimation()
{
	delete m_Player;
	m_Player = nullptr;
}

void PlayerAnimation::Update(float elapsedSec)
{
	switch (m_Player->GetState())
	{
	case Player::State::dead:
		break;
	default:
		break;
	}
}
