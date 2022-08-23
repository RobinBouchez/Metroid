#pragma once
#include "GameObject.h"

class Texture;
class Animation;
class World;
class Player;
class Vitals;

class Enemy : public GameObject
{
public:
	enum class Direction
	{
		right = 0, down = 1, left = 2, up = 3
	};


	Enemy(const Point2f& position);
	virtual ~Enemy();


	virtual void Update(float elapsedSec) override {};
	virtual void Update(float elapsedSec, World* level, Player* player);
	virtual void Draw() const override;

	virtual std::string GetTag() const;

	void TakeHit();

protected:
	Texture* m_pTexture;
	Vitals* m_Vitals;
	std::string m_Tag;

	void CalculateTexture(const std::string& filename, const int columns);

private:
	void SpawnPickup();

	Animation* m_pAnimation;
	float m_HorizontalSpeed;
	float m_CurrentHealth;
	int m_Columns;
};

