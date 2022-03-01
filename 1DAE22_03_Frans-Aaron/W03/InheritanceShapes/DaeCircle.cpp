#include "pch.h"		
#include "DaeCircle.h"
#include "utils.h"

DaeCircle::DaeCircle(const Point2f& center, float diameter, const Color4f& color, bool isFilled)
	: DaeEllipse(center, diameter, diameter, color, isFilled)
{
}

void DaeCircle::Draw() const
{
	DaeEllipse::Draw();
}

void DaeCircle::Translate(const Vector2f& tr)
{
	m_Center += tr;
}


