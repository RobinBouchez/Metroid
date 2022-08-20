#include "pch.h"
#include "Camera.h"

#include <algorithm>

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{}
	, m_Scale{ 1.1f }
	, m_CameraPos{}
{

}

void Camera::SetLevelBoundaries(const Rectf& level)
{
	m_LevelBoundaries.bottom = level.bottom;
	m_LevelBoundaries.left = level.left;
	m_LevelBoundaries.width = level.width;
	m_LevelBoundaries.height = level.height;

}

Point2f Camera::GetPosition() const
{
	return m_CameraPos;
}

void Camera::Transform(const Rectf& target)
{
	m_CameraPos = Track(target);
	//m_CameraPos.x = std::clamp(m_CameraPos.x, 0.f, target.left + m_Width);
	//m_CameraPos.y = std::clamp(m_CameraPos.y, 0.f, target.bottom + m_Height);

	Clamp(m_CameraPos);
	glScalef(m_Scale, m_Scale, 0);
	glTranslatef(-m_CameraPos.x, -m_CameraPos.y, 0);
}

Point2f Camera::Track(const Rectf& target) const 
{
	return Point2f{ target.left + target.width / 2 - m_Width / 2, target.bottom + target.height / 2 - m_Height / 2 };
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	const float textureBorderWidth = 115; //width of the wall of the level in pixels

	if (bottomLeftPos.x <= m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	else if (bottomLeftPos.x >= m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width + textureBorderWidth)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width + textureBorderWidth;/// 2 - 525.f;
	}
	
	if (bottomLeftPos.y <= m_LevelBoundaries.bottom)
	{		
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	else if (bottomLeftPos.y >= m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height;
	}
	
}
