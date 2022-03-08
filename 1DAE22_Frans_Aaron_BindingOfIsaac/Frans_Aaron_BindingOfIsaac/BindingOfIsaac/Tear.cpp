#include "pch.h"
#include "Tear.h"
#include "Sprite.h"
#include "Texture.h"

Tear::Tear(Texture* texture)
	: m_State{ TearState::inactive }
	, m_Height{ 0 }
{
	m_pTearSprite = new Sprite(texture, 8, 4, 1 / 25.0f, 1, 1);
	mTearSpriteLeftBottom = Point2f{ m_pTearSprite->GetFrameWidth() * 4, m_pTearSprite->GetFrameHeight() * 1 };
}

Tear::~Tear()
{
	delete m_pTearSprite;
	m_pTearSprite = nullptr;
}

void Tear::Draw() const
{
	m_pTearSprite->Draw(Point2f{ m_TearShape.center.x - m_TearShape.radius / 2.0f,
		 m_TearShape.center.y - m_TearShape.radius / 2.0f }, mTearSpriteLeftBottom);
}

void Tear::Update(float elapsedSec)
{
	if (m_TearShape.center.x > 500)
		m_State = TearState::inactive;
	m_pTearSprite->Update(elapsedSec);
	m_TearShape.center.x += m_Velocity.x * elapsedSec;
	m_TearShape.center.x += m_Velocity.y * elapsedSec;
}

Tear::TearState Tear::GetState() const
{
	return m_State;
}

void Tear::SetState(TearState state)
{
	m_State = state;
}

void Tear::SetVelocity(Vector2f velocity)
{
	m_Velocity = velocity;
}

void Tear::SetTearShape(Circlef tearShape)
{
	m_TearShape = tearShape;
}

void Tear::SetHeight(float height)
{
	m_Height = height;
}
