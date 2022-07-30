#pragma once
#include "Vector2f.h"

class GameObject;
class TextureManager;
class Animation;

class Enemy : public GameObject
{
public:
	enum class State
	{
		alive,
		dead
	};

	Enemy(Point2f& position);
	virtual ~Enemy();

	virtual void Update(float ElapsedSec);
	virtual void Draw() const override;
	
protected:
	Rectf m_Boundaries;
	Point2f m_Position;
	TextureManager* m_pTexture;


private:
	Animation* m_pAnimation;
	State m_State;

	float m_HorizontalSpeed;

	float m_Health;
	float m_Damage;
	const int m_Rows;
};

