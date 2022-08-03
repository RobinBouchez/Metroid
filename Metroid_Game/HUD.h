#pragma once

class Texture;
class HUD final
{
public:
	HUD();
	~HUD();

	void Draw(float& pos, float &Ypos) const;
	void Update(float elapsedSec);

private:
	//Data members
	Texture* m_pTexture;
	const int m_FontSize;
	const Color4f m_FontColor;
	std::string m_StringText;
	const float m_Ypos;
	//const Point2f m_WindowPos;


	//Helper Functions
	void DisplayScore();
	void UpdateScore();

};

