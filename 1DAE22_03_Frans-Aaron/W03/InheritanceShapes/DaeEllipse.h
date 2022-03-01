#pragma once
#include "Vector2f.h"
#include "DaeShape.h"

class DaeEllipse : public DaeShape
{
public:
	DaeEllipse(const Point2f& center, float width, float height, const Color4f& color, bool isFilled);

	void Draw() const;
	void Translate(const Vector2f& tr);

protected:
	Color4f m_Color;
	bool m_IsFilled;
};


