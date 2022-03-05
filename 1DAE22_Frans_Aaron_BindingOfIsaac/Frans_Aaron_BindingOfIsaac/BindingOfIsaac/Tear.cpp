#include "pch.h"
#include "Tear.h"
#include "Sprite.h"

Tear::Tear()
	: m_State{ TearState::inactive }
	, m_Height{ 0 }
	, m_pTearSprite{}
{
}

Tear::~Tear()
{
}

void Tear::Draw() const
{
}

void Tear::Update(float elapsedSec)
{
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
