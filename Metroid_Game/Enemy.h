#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
class Animation;
class World;

class Enemy : public GameObject
{
public:
	enum class State
	{
		alive,
		dead
	};

	enum class Direction
	{
		right = 0, down = 1, left = 2, up = 3
	};


	Enemy(const Point2f& position);
	virtual ~Enemy();

	virtual void Update(float ElapsedSec) override;
	virtual void Draw() const override;
	
protected:
	Rectf m_Boundaries;
	Point2f m_Position;
	Texture* m_pTexture;
	State m_State;
	World* m_pWorld;

	void CalculateTexture(const std::string& filename, const int columns);

private:
	Animation* m_pAnimation;

	float m_HorizontalSpeed;

	float m_Health;
	float m_Damage;
	int m_Columns;
};

