#include "pch.h"
#include "Ball.h"
#include "utils.h"

Ball::Ball(const Point2f& center, const Vector2f& velocity, const Color4f& color, float radius)
	: m_Center{ center }
	, m_Velocity{ velocity }
	, m_Color{ color }
	, m_Radius{ radius }
{
}

void Ball::Update(float elapsedSeconds, const Rectf& r)
{
	const float left{ r.left };
	const float bottom{ r.bottom };
	const float right{ r.left + r.width };
	const float top{ r.bottom + r.height };

	m_Center.x += m_Velocity.x * elapsedSeconds;
	m_Center.y += m_Velocity.y * elapsedSeconds;

	if (m_Center.x + m_Radius > right && m_Velocity.x > 0) 
	{
		m_Velocity.x *= -1; 
		GenerateColor();
	}
	if (m_Center.y + m_Radius > top && m_Velocity.y > 0)
	{ 
		m_Velocity.y *= -1; 
		GenerateColor();
	}
	if (m_Center.x - m_Radius < left && m_Velocity.x < 0)
	{ 
		m_Velocity.x *= -1; 
		GenerateColor();
	}
	if (m_Center.y - m_Radius < bottom && m_Velocity.y < 0)
	{ 
		m_Velocity.y *= -1; 
		GenerateColor();
	}
}

void Ball::Draw() const
{
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	utils::FillEllipse(m_Center, m_Radius, m_Radius);
}

void Ball::GenerateColor()
{
	m_Color = Color4f{ rand() % 256 / 255.0f, rand() % 256 / 255.0f, rand() % 256 / 255.0f, 1.0f };
}

