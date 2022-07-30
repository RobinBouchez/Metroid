#pragma once
class Player;
class SoundManager;
class Morphball
{
public:
	Morphball();
	virtual ~Morphball();

	void Draw() const;
	void Update(float elapsedSec);
	
	bool CheckIfhit(Player* player);

	static bool m_IsHit;

private:
	Point2f m_Position;
	Rectf m_DstRect;
	Rectf m_SrcRect;

	Animation* m_pAnimation;
	SoundManager* m_pSoundManager;
	Texture* m_pTexture;

	int m_Rows;

	void ChangeColor();
};

