#include "pch.h"
#include "Camera.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{}
	, m_Scale{ 1.1f }
{
}

Camera::~Camera()
{
}

void Camera::SetLevelBoundaries(float x, float y, float width, float height)
{
	m_LevelBoundaries.bottom = y;
	m_LevelBoundaries.left = x;
	m_LevelBoundaries.width = width;
	m_LevelBoundaries.height = height;

}

void Camera::Transform(const Rectf& target) const
{
	Point2f cameraPos;
	cameraPos = Track(target);
	Clamp(cameraPos);
	glScalef(m_Scale, m_Scale, 0);
	glTranslatef(-cameraPos.x, 0, 0);
}

Point2f Camera::Track(const Rectf& target) const 
{
	return Point2f{ target.left + target.width / 2 - m_Width / 2, target.bottom + target.height / 2 - m_Height / 2 };
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x <= m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	if (bottomLeftPos.x >= m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width;
	}
	
	if (bottomLeftPos.y <= m_LevelBoundaries.bottom)
	{		
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	if (bottomLeftPos.y >= m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height;
	}
	
}
