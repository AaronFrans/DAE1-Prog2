#pragma once
class DaeShape
{
public:
	DaeShape(const Point2f& center, float width, float height);


protected:
	Point2f m_Center;
	float m_Width;
	float m_Height;

};

