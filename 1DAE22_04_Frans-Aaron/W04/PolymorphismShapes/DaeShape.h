#pragma once
#include "Vector2f.h"

class DaeShape
{
public:
	DaeShape(const Point2f& center, float width, float height);
	virtual ~DaeShape();

	void virtual Draw() const = 0;

	void Translate(const Vector2f& tr);
protected:
	Point2f m_Center;
	float m_Width;
	float m_Height;

};

