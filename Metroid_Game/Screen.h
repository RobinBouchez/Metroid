#pragma once
class Texture;

class Screen 
{
public:
	Screen() = default;
	virtual ~Screen();

protected:
	Texture* m_pTexure;

	bool m_IsActive;
};

