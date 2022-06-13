#pragma once
#include "Floor.h"

class Camera final
{
public:
	Camera(float width, float height);


	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Point2f& targetCenter) const;

	void Transition(const float transitionedDistance, Floor::TransitionDirection direction);

	Rectf GetCameraView(const Point2f& targetCenter) const;
private:
	float m_Width;
	float m_Height;

	Rectf m_LevelBoundaries;

	void Clamp(Point2f& centerPos) const;
};

