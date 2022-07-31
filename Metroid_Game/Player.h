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
		idle,
		running,
		jumping,
		lookingUp,
		crouching
	};

	Player(Point2f& position);
	virtual ~Player();

	virtual void Draw() const override;
	
	void Update(float elapsedSec, World* level);
	virtual void Update(float elapsedSec) override;

	int GetScore();

	Rectf m_Shape;
	static int m_Score;


private:
	State m_State;

	Animation* m_pAnimation;
	Texture* m_pTexture;
	Texture* m_pBallTexture;
	Bullet* m_pBullet;
	
	Rectf m_SourceClip;
	Rectf m_BallTextureClip;
	Rectf m_TextureClip;
	
	Rectf m_BallShape;

	int m_Rows;
	int m_Cols;

	bool m_IsRolling;
	bool m_IsShooting;
	
	const float m_RotSpeed;
	float m_Angle;


	void SetTexture();
	void UpdateMovement(float elapsedSec, World* level);
};