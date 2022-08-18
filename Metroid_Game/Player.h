#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
class Bullet;
class World;
class Animation;
class SoundManager;

class Player : public GameObject
{
public:
	enum class State
	{
		dead,
		idle,
		running,
		jumping,
		lookingUp,
		crouching
	};

	enum class AimDirection
	{
		up, left, right
	};


	Player(Point2f& position);
	virtual ~Player();

	virtual void Draw() const override;
	
	void Update(float elapsedSec, World* &level);
	virtual void Update(float elapsedSec) override;

	void Shoot();

	Rectf GetShape() const;
	int GetScore() const;

	enum class State GetState() const;


	static int m_Score;


private:
	AimDirection m_AimDirection;
	State m_State;

	Animation* m_pAnimation;
	Texture* m_pPlayerTexture;
	Texture* m_pBallTexture;

	Rectf m_SourceClip;
	Rectf m_BallTextureClip;
	Rectf m_TextureClip;
	
	Rectf m_Shape;

	Rectf m_BallShape;

	int m_Rows;
	int m_Cols;

	bool m_IsRolling;
	bool m_IsShooting;
	
	float m_JumpSpeed;

	const float m_RotSpeed;
	float m_Angle;

	float m_Timer;
	bool m_HasShot;
	float m_Cooldown;

	void SetTexture();
	void UpdateMovement(float elapsedSec, World* &level);
};