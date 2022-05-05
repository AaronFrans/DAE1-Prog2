#include "pch.h"
#include "Rock.h"
#include "Sprite.h"
#include "utils.h"

Rock::Rock(Texture* objectTexture, Point2f center, float size)
	: GameObject(objectTexture, 4, 1, center, size)
	, m_IsBroken{ false }
{
	m_RockType = utils::GetRand(0, 2);
}

void Rock::Draw() const
{
	Point2f srcBottomLeft;
	!m_IsBroken? srcBottomLeft = Point2f{ m_pSprite->GetFrameWidth() * m_RockType, 0 } :
				srcBottomLeft = Point2f{ m_pSprite->GetFrameWidth() * 3, 0 };

	m_pSprite->Draw(m_DrawShape, srcBottomLeft);
}

bool Rock::IsNotDestroyed() const
{
	return !m_IsBroken;
}
