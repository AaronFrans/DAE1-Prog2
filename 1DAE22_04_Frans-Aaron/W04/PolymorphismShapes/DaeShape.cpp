#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const Point2f& center, float width, float height)
	: m_Center{ center }
	, m_Width{ width }
	, m_Height{ height }
{
}

DaeShape::~DaeShape()
{
}

void DaeShape::Translate(const Vector2f& tr)
{
	m_Center += tr;
}
