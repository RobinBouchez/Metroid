#pragma once

class Screen 
{
public:
	Screen(const Point2f& position);
	virtual ~Screen();

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;

	Rectf GetBoundaries() const;
	void SetIsActive(bool value);
	
	bool IsActive();
	bool HasPlayed();
	void Continue(bool value);

protected:
	bool m_IsActive{};
	bool m_HasPlayed;

	const Point2f m_ScreenPos;
	Rectf m_Boundaries;
	bool m_Continue;

};

