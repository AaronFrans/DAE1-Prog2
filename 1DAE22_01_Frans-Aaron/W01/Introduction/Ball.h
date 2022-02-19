#pragma once
#include "Vector2f.h"
class Ball
{
public:
	Ball(const Point2f& center, const Vector2f& velocity, const Color4f& color, float radius);
	void Update(float elapsedSeconds, const Rectf& r);
	void Draw() const;

private:
	Point2f m_Center;
	Vector2f m_Velocity;
	Color4f m_Color;
	float m_Radius;

	void GenerateColor( );
};

