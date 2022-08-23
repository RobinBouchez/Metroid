#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
class Bullet;
class World;
class Animation;
class SoundManager;
class Vitals;

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


	Player(const Point2f& position);
	Player(const Point2f& position, const float health);
	virtual ~Player();

	virtual void Draw() const override;
	
	void Update(float elapsedSec, World* &level);
	virtual void Update(float elapsedSec) override;

	void Shoot();

	void SetPosition(const Point2f& pos);
	int GetScore() const;

	enum class State GetState() const;

	Vitals* GetVitals() const;

	static int m_Score;

	Rectf m_Shape;
private:
	AimDirection m_AimDirection;
	State m_State;

	Animation* m_pAnimation;
	Texture* m_pPlayerTexture;
	Texture* m_pBallTexture;
	Texture* m_pDeathTexture;
	Vitals* m_Vitals;

	Rectf m_SourceClip;
	Rectf m_BallTextureClip;
	Rectf m_TextureClip;
	
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

	bool m_IsMovingLeft;

	float m_HorizontalSpeed;

	void SetTexture();
	void UpdateMovement(float elapsedSec, World* &level);
	void UpdateVitals(float elapsedSec);
};