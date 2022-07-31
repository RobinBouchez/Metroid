#include "pch.h"
#include "Player.h"
#include "Texture.h"	
#include "Bullet.h"
#include "Animation.h"
#include "World.h"
#include "Morphball.h"
#include "SoundManager.h"

int Player::m_Score = 0;

Player::Player(Point2f& position)
	: m_pTexture{ new Texture("Resources/Samus.png") }
	, m_pBallTexture{ new Texture("Resources/morphball.png")}
	, m_State{ State::idle }
	, m_SourceClip{}
	, m_TextureClip{}
	, m_Shape{}
	, m_Rows{ 4 }
	, m_Cols{ 6 }
	, m_pAnimation{ new Animation(m_Rows) }
	, m_IsRolling{false}
	, m_Angle{}
	, m_RotSpeed{ 1200.f }
	, m_pBullet{ new Bullet() }
	, m_IsShooting{false}
{
	m_Shape.left = position.x;
	m_Shape.bottom = position.y;
	m_Shape.width = m_pTexture->GetWidth() / m_Rows;
	m_Shape.height = m_pTexture->GetHeight() / m_Cols;

	m_BallShape.left = m_Shape.left;
	m_BallShape.bottom = m_Shape.bottom;
	m_BallShape.width = m_pBallTexture->GetWidth();
	m_BallShape.height = m_pBallTexture->GetHeight();
}

Player::~Player()
{
	delete m_pTexture;
	m_pTexture = nullptr;

	delete m_pBallTexture;
	m_pBallTexture = nullptr;
	
	delete m_pBullet;
	m_pBullet = nullptr;

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
			m_pTexture->Draw(m_TextureClip, m_SourceClip);
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
		m_pTexture->Draw(m_TextureClip, m_SourceClip);
	}

	if (m_IsShooting)
	{
		m_pBullet->Draw();

	}
}

void Player::Update(float elapsedSec, World* level)
{
	UpdateMovement(elapsedSec, level);
	SetTexture();
	
	m_pAnimation->Update(elapsedSec);
	m_pBullet->Update(elapsedSec);

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
	
}

void Player::Update(float elapsedSec)
{
}

int Player::GetScore()
{
	return m_Score;
}

void Player::SetTexture()
{
	switch (m_State)
	{
	case Player::State::idle:
		m_SourceClip.left = 0.f;
		m_SourceClip.bottom = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.height = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.width  = m_pTexture->GetWidth() / m_Rows;
		break;
	case Player::State::running:
		m_SourceClip.left = m_pAnimation->m_AnimationFrame * m_pTexture->GetWidth() / m_Rows;
		m_SourceClip.bottom = (m_pTexture->GetHeight() / m_Cols) * 2;
		m_SourceClip.height = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;
		break;
	case Player::State::jumping:
		m_IsRolling = false;
		m_SourceClip.left = 0;
		m_SourceClip.bottom = m_pTexture->GetHeight() - m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.height = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;
		break;
	case Player::State::lookingUp:
		m_IsRolling = false;
		m_SourceClip.left = 0;
		m_SourceClip.bottom = (m_pTexture->GetHeight() / m_Cols) * 4;
		m_SourceClip.height = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;
		break;
	case Player::State::crouching:
		m_SourceClip.left = 0;
		m_SourceClip.bottom = 0;
		m_SourceClip.height = m_pTexture->GetHeight() / m_Cols;
		m_SourceClip.width = m_pTexture->GetWidth() / m_Rows;
		break;
	}
	
	m_BallTextureClip.left = m_Shape.left;
	m_BallTextureClip.bottom = m_Shape.bottom;
	m_BallTextureClip.height = m_pBallTexture->GetHeight();
	m_BallTextureClip.width = m_pBallTexture->GetWidth();
	
	m_TextureClip.left   = m_Shape.left;
	m_TextureClip.bottom = m_Shape.bottom;
	m_TextureClip.height = m_pTexture->GetHeight() / m_Cols;
	m_TextureClip.width  = m_pTexture->GetWidth() / m_Rows;
}


void Player::UpdateMovement(float elapsedSec, World* level)
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
		m_State = State::running;
		m_IsMovingLeft = false;
		m_Velocity.x = m_HorizontalSpeed * elapsedSec;
	}
	else if (State[SDL_SCANCODE_LEFT] || State[SDL_SCANCODE_A])
	{
		m_State = State::running;
		m_IsMovingLeft = true;
		m_Velocity.x = -m_HorizontalSpeed * elapsedSec;
	}
	else if (State[SDL_SCANCODE_UP] || State[SDL_SCANCODE_W])
	{
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
			SoundManager::GetInstance().Play("Jump");
		}
	}
	else if (State[SDL_SCANCODE_F])
	{
		m_IsShooting = true;
	}
	else
	{
		if (!m_IsRolling)
		{
			m_State = State::idle;
		}
	}
	
	m_Shape.left += m_Velocity.x;
	m_Shape.bottom += m_Velocity.y;
}
