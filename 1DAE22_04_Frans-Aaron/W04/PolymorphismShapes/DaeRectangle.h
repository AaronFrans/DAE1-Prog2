#pragma once
#include "Vector2f.h"
#include "DaeShape.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle(const Point2f& center, float width, float height, const Color4f& color);
	virtual ~DaeRectangle();

	void virtual Draw() const override;

protected:
	Color4f m_Color;
};


