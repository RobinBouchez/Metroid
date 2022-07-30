#pragma once
class Texture;
class Animation;

class Bullet
{
public:
	Bullet();
	virtual ~Bullet();

	void Draw() const;
	void Update(float elapsedSec);
	
	Point2f m_Position;

private:
	Animation* m_pAnimation;
	Texture* m_pTexture;

	const int m_Rows;
};

