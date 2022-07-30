#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
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
	Texture* m_pTexture;
	
	std::string m_FileName;

private:
	Animation* m_pAnimation;
	State m_State;

	float m_HorizontalSpeed;

	float m_Health;
	float m_Damage;
	const int m_Rows;
};

