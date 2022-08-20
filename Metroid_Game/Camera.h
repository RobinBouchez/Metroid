#pragma once

class Camera final
{
public:
	Camera() = default;
	Camera(float width, float height);
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	void SetLevelBoundaries(const Rectf& level);

	Point2f GetPosition() const;
	void Transform(const Rectf& target);

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;
	const float m_Scale;
	Point2f m_CameraPos;


	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;

};

