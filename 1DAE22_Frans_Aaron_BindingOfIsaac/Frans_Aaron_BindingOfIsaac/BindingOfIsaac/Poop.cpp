#include "pch.h"
#include "Poop.h"
#include "Sprite.h"
#include "utils.h"

Poop::Poop(Texture* objectTexture, int nrColls, int nrRows, Point2f center, float size)
	: GameObject{ objectTexture, nrColls, nrRows, center, size }
	, m_NrHitsTaken{ 0 }
	, m_NrStates{ (nrColls * nrRows) - 1 }
{
}

void Poop::Draw() const
{
	Point2f srcBottomLeft{ m_pSprite->GetFrameWidth() * m_NrHitsTaken, 0 };
	m_pSprite->Draw(m_Shape, srcBottomLeft);
}

void Poop::IsHit()
{
	++m_NrHitsTaken;
}

bool Poop::IsNotDestroyed() const
{
	return m_NrHitsTaken < m_NrStates;
}
