#include "pch.h"
#include "Player.h"
#include "Texture.h"	
#include "Bullet.h"
#include "Animation.h"
#include "World.h"
#include "Morphball.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "BulletManager.h"
#include <iostream>
int Player::m_Score = 0;

Player::Player(Point2f& position)
	: m_State{ State::idle }
	, m_SourceClip{}
	, m_TextureClip{}
	, m_Shape{}
	, m_Rows{ 4 }
	, m_Cols{ 6 }
	, m_pAnimation{ new Animation(m_Rows) }
	, m_IsRolling{false}
	, m_Angle{}
	, m_RotSpeed{ 1200.f }
	, m_IsShooting{false}
	, m_AimDirection{}
	, m_Timer{}
	, m_Cooldown{ 0.1f }
	, m_HasShot{}
{

	m_pPlayerTexture = TextureManager::GetInstance().CreateTexture("Samus");
	m_pBallTexture = TextureManager::GetInstance().CreateTexture("morphball");

	m_Shape.left = position.x;
	m_Shape.bottom = position.y;
	m_Shape.width = m_pPlayerTexture->GetWidth() / m_Rows;
	m_Shape.height = m_pPlayerTexture->GetHeight() / m_Cols;

	m_BallShape.left = m_Shape.left;
	m_BallShape.bottom = m_Shape.bottom;
	m_BallShape.width = m_pBallTexture->GetWidth();
	m_BallShape.height = m_pBallTexture->GetHeight();

	SoundManager::GetInstance().CreateSound("Jump");
	SoundManager::GetInstance().CreateSound("Roll");

}

Player::~Player()
{	
	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void Player::Draw() const
{
	if (m_IsMovingLeft)
	{
		if (m_IsRolling)
		{
			glPushMatrix();
			glTranslatef(m_Shape.left + m_BallShape.width / 2, m_Shape.bottom + m_BallShape.height / 2, 0);
			glRotatef(m_Angle, 0, 0, 1);
			glTranslatef(-(m_Shape.left + m_BallShape.width / 2), -(m_Shape.bottom + m_BallShape.height / 2), 0);
			m_pBallTexture->Draw(m_BallTextureClip);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(m_Shape.left, 0, 0);
			glScalef(-1, 1, 1);
			glTranslatef(-m_Shape.left - m_Shape.width, 0, 0);
			m_pPlayerTexture->Draw(m_TextureClip, m_SourceClip);
			glPopMatrix();
		}
	}
	else if (m_IsRolling)
	{
		glPushMatrix();
			glTranslatef(m_Shape.left + m_BallShape.width / 2, m_Shape.bottom + m_BallShape.height / 2, 0);
			glRotatef(m_Angle, 0, 0, -1);
			glTranslatef(-(m_Shape.left + m_BallShape.width / 2), -(m_Shape.bottom + m_BallShape.height / 2), 0);
			m_pBallTexture->Draw(m_BallTextureClip);
		glPopMatrix();
	}
	else
	{
		m_pPlayerTexture->Draw(m_TextureClip, m_SourceClip);
	}
}

void Player::Update(float elapsedSec, World* &level)
{
	UpdateMovement(elapsedSec, level);
	SetTexture();
	
	m_pAnimation->Update(elapsedSec);

	if (!m_IsRolling)
	{
		level->HandleCollision(m_Shape, m_Velocity);
	}
	else
	{
		m_BallShape.left = m_Shape.left;
		m_BallShape.bottom = m_Shape.bottom;
		level->HandleCollision(m_BallShape, m_Velocity);
		m_Shape.left = m_BallShape.left;
		m_Shape.bottom = m_BallShape.bottom;
	}

	if (m_HasShot)
	{
		m_Timer += elapsedSec;
		if (m_Timer >= m_Cooldown)
		{
			m_Timer = 0;
			m_HasShot = false;
		}
	}
}

void Player::Update(float elapsedSec)
{
}

void Player::Shoot()
{
	if (!m_HasShot)
	{
		Vector2f bulletVelocity{};
		switch (m_AimDirection)
		{
		case AimDirection::left:
			bulletVelocity = Vector2f{ -1, 0 };
			break;
		case AimDirection::right:
			bulletVelocity = Vector2f{ 1, 0 };
			break;
		case AimDirection::up:
			bulletVelocity = Vector2f{ 0, 1 };
			break;
		}
		BulletManager::GetInstance().Create(new Bullet(Point2f{ m_Shape.left + 10, m_Shape.bottom + 50 }, bulletVelocity));
		m_HasShot = true;
	}
}

enum class Player::State Player::GetState() const
{
	return m_State;
}

Rectf Player::GetShape() const
{
	return m_Shape;
}

int Player::GetScore() const
{
	return m_Score;
}

void Player::SetTexture()
{
	switch (m_State)
	{
	case Player::State::idle:
		m_SourceClip.left = 0.f;
		m_SourceClip.bottom = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.width  = m_pPlayerTexture->GetWidth() / m_Rows;
		break;
	case Player::State::running:
		m_SourceClip.left = m_pAnimation->m_AnimationFrame * m_pPlayerTexture->GetWidth() / m_Rows;
		m_SourceClip.bottom = (m_pPlayerTexture->GetHeight() / m_Cols) * 2;
		m_SourceClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pPlayerTexture->GetWidth() / m_Rows;
		break;
	case Player::State::jumping:
		m_IsRolling = false;
		m_SourceClip.left = 0;
		m_SourceClip.bottom = m_pPlayerTexture->GetHeight() - m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pPlayerTexture->GetWidth() / m_Rows;
		break;
	case Player::State::lookingUp:
		m_IsRolling = false;
		m_SourceClip.left = 0;
		m_SourceClip.bottom = (m_pPlayerTexture->GetHeight() / m_Cols) * 4;
		m_SourceClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pPlayerTexture->GetWidth() / m_Rows;
		break;
	case Player::State::crouching:
		m_SourceClip.left = 0;
		m_SourceClip.bottom = 0;
		m_SourceClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pPlayerTexture->GetWidth() / m_Rows;
		break;
	}
	
	m_BallTextureClip.left = m_Shape.left;
	m_BallTextureClip.bottom = m_Shape.bottom;
	m_BallTextureClip.height = m_pBallTexture->GetHeight();
	m_BallTextureClip.width = m_pBallTexture->GetWidth();
	
	m_TextureClip.left   = m_Shape.left;
	m_TextureClip.bottom = m_Shape.bottom;
	m_TextureClip.height = m_pPlayerTexture->GetHeight() / m_Cols;
	m_TextureClip.width  = m_pPlayerTexture->GetWidth() / m_Rows;
}


void Player::UpdateMovement(float elapsedSec, World* &level)
{
	if (m_Velocity.x > 0)
	{
		m_Velocity.x -= m_Acceleration.x * elapsedSec;
	}
	else
	{
		m_Velocity.x += m_Acceleration.x * elapsedSec;
	}
	m_Angle += m_RotSpeed * elapsedSec;
	m_Velocity.y += m_Acceleration.y * elapsedSec;
	m_HorizontalSpeed += elapsedSec;
	m_JumpSpeed += elapsedSec;

	const UINT8* State = SDL_GetKeyboardState(NULL);
	if (State[SDL_SCANCODE_RIGHT] || State[SDL_SCANCODE_D])
	{

		m_AimDirection = AimDirection::right;
		m_State = State::running;
		m_IsMovingLeft = false;
		m_Velocity.x = m_HorizontalSpeed * elapsedSec;
	}
	else if (State[SDL_SCANCODE_LEFT] || State[SDL_SCANCODE_A])
	{
		m_State = State::running;
		m_AimDirection = AimDirection::left;
		m_IsMovingLeft = true;
		m_Velocity.x = -m_HorizontalSpeed * elapsedSec;
	}
	else if (State[SDL_SCANCODE_UP] || State[SDL_SCANCODE_W])
	{
		if (State[SDL_SCANCODE_F])
		{
			m_AimDirection = AimDirection::up;
			Shoot();
		}
		m_State = State::lookingUp;
		m_IsRolling = false;
	}
	else if (State[SDL_SCANCODE_DOWN] || State[SDL_SCANCODE_S])
	{
		if (Morphball::m_IsHit)
		{
			m_IsRolling = true;

			SoundManager::GetInstance().Play("Roll");
		}
	}
	else if (State[SDL_SCANCODE_SPACE])
	{
		m_State = State::jumping;

		m_IsRolling = false;

		if (level->IsOnGround(m_Shape))
		{
			m_Velocity.y += m_JumpSpeed * elapsedSec;
			//SoundManager::GetInstance().Play("Jump");
		}
	}
	else if (State[SDL_SCANCODE_F])
	{
		m_IsShooting = true;
		if (m_State != State::lookingUp)
		{
			Shoot();
		}
	}
	else
	{
		if (!m_IsRolling)
		{
			m_State = State::idle;
		}
	}
	
	//Prevent camera shake
	if (abs(m_Velocity.x) < 1 && abs(m_Velocity.y) < 1)
	{
		return;
	}
	m_Shape.left += m_Velocity.x;
	m_Shape.bottom += m_Velocity.y;
}
