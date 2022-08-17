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

protected:
	bool m_IsActive{};
	const Point2f m_ScreenPos;
	Rectf m_Boundaries;

};

