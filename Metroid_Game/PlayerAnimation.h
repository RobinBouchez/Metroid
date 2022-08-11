#pragma once
#include "Animation.h"

class Player;

class PlayerAnimation : public Animation
{
public:
	enum class State
	{
		alive,
		dead,
		isHit,
		isRolling,
		isJumping
	};


	PlayerAnimation(const int& frameCount, const float& speed);
	virtual ~PlayerAnimation();

	virtual void Update(float elapsedSec) override;

private:
	Player* m_Player;


};

