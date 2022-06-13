#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{ 0, 0, width, height }
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Point2f& targetCenter) const
{
	Point2f center = targetCenter;
	Clamp(center);
	glTranslatef(-(center.x - m_Width / 2.0f), -(center.y - m_Height / 2.0f), 0);
}

void Camera::Transition(const float transitionedDistance, Floor::TransitionDirection direction)
{
	switch (direction)
	{
	case Floor::TransitionDirection::up:
		m_LevelBoundaries.bottom += transitionedDistance;
		break;
	case Floor::TransitionDirection::down:
		m_LevelBoundaries.bottom -= transitionedDistance;
		break;
	case Floor::TransitionDirection::left:
		m_LevelBoundaries.left -= transitionedDistance;
		break;
	case Floor::TransitionDirection::right:
		m_LevelBoundaries.left += transitionedDistance;
		break;
	default:
		break;
	}
}

Rectf Camera::GetCameraView(const Point2f& targetCenter) const
{
	Point2f center = targetCenter;
	Clamp(center);
	return Rectf{ center.x - m_Width / 2.0f, center.y - m_Height / 2.0f, m_Width, m_Height };
}

void Camera::Clamp(Point2f& centerPos) const
{
	float cameraWidthHalf = m_Width / 2.0f;

	float cameraBoundaryDifference = (centerPos.x - cameraWidthHalf) - m_LevelBoundaries.left;
	if (cameraBoundaryDifference < 0)
		centerPos.x -= cameraBoundaryDifference;

	cameraBoundaryDifference = (centerPos.x + cameraWidthHalf) - (m_LevelBoundaries.left + m_LevelBoundaries.width);
	if (cameraBoundaryDifference > 0)
		centerPos.x -= cameraBoundaryDifference;


	float cameramHeightHalf = m_Height / 2.0f;

	cameraBoundaryDifference = (centerPos.y - cameramHeightHalf) - m_LevelBoundaries.bottom;
	if (cameraBoundaryDifference < 0)
		centerPos.y -= cameraBoundaryDifference;

	cameraBoundaryDifference = (centerPos.y + cameramHeightHalf) - (m_LevelBoundaries.bottom + m_LevelBoundaries.height);
	if (cameraBoundaryDifference > 0)
		centerPos.y -= cameraBoundaryDifference;
}
