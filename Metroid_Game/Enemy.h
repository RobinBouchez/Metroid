#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Texture;
class Animation;
class World;
class Player;

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


	virtual void Update(float elapsedSec) override {};
	virtual void Update(float elapsedSec, World* level, Player* player);
	virtual void Draw() const override;

	bool GetIsActive() const;

	Rectf GetBoundaries() const;
	void TakeHit();
	
protected:
	Rectf m_Boundaries;
	Point2f m_Position;
	Texture* m_pTexture;
	State m_State;

	void CalculateTexture(const std::string& filename, const int columns);

private:
	Animation* m_pAnimation;

	float m_HorizontalSpeed;

	bool m_IsActive;

	float m_CurrentHealth;
	const float m_Health;
	float m_Damage;
	int m_Columns;
};

