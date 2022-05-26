#include "pch.h"
#include "Poop.h"
#include "Sprite.h"
#include "utils.h"

Poop::Poop(Texture* objectTexture, Point2f center, float size)
	: GameObject{ objectTexture,5, 1, center, size }
	, m_NrHitsTaken{ 0 }
	, m_NrStates{ (5 * 1) - 1 }
{
}

Poop::Poop(const Poop& rhs)
	: GameObject{ }
	, m_NrHitsTaken{ rhs.m_NrHitsTaken }
	, m_NrStates{ rhs.m_NrStates }
{
	m_pSprite = new Sprite{ *rhs.m_pSprite };
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;
}

Poop& Poop::operator=(const Poop& rhs)
{
	m_NrHitsTaken = rhs.m_NrHitsTaken;
	m_NrStates = rhs.m_NrStates;

	m_pSprite = new Sprite{ *rhs.m_pSprite };
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;

	return *this;
}

Poop::~Poop()
{
}

void Poop::Draw() const
{
	Point2f srcBottomLeft{ m_pSprite->GetFrameWidth() * m_NrHitsTaken, 0 };
	m_pSprite->Draw(m_DrawShape, srcBottomLeft);
}

void Poop::IsHit()
{
	++m_NrHitsTaken;
}

bool Poop::IsNotDestroyed() const
{
	return m_NrHitsTaken < m_NrStates;
}

GameObject* Poop::Clone() const
{
	return new Poop(*this);
}
