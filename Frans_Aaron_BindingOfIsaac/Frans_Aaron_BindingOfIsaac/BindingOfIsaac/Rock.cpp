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

Rock::Rock(const Rock& rhs)
	: GameObject{}
	, m_IsBroken{ rhs.m_IsBroken }
{
	m_RockType = utils::GetRand(0, 2);

	m_pSprite = new Sprite{ *rhs.m_pSprite };
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;
}

Rock& Rock::operator=(const Rock& rhs)
{
	m_IsBroken = rhs.m_IsBroken;
	m_RockType = utils::GetRand(0, 2);

	m_pSprite = new Sprite{ *rhs.m_pSprite };
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;

	return *this;
}

Rock::~Rock()
{
}

void Rock::Draw() const
{
	Point2f srcBottomLeft;
	!m_IsBroken ? srcBottomLeft = Point2f{ m_pSprite->GetFrameWidth() * m_RockType, 0 } :
		srcBottomLeft = Point2f{ m_pSprite->GetFrameWidth() * 3, 0 };

	m_pSprite->Draw(m_DrawShape, srcBottomLeft);
}

bool Rock::IsNotDestroyed() const
{
	return !m_IsBroken;
}

GameObject* Rock::Clone() const
{
	return new Rock(*this);
}
