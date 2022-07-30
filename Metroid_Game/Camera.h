#pragma once

class Camera
{
public:
	Camera(float width, float height);
	~Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	void SetLevelBoundaries(float x, float y, float width, float height);
	
	void Transform(const Rectf& target) const;
private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;
	const float m_Scale;

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;

};

