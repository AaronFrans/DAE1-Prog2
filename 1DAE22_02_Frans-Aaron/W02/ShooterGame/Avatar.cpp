#include "pch.h"
#include "Avatar.h"
#include "utils.h"

Avatar::Avatar()
	: Avatar(Point2f{ 0,0 }, 0, 0)
{
}

Avatar::Avatar(const Point2f& center, float width, float height)
	: m_Center{ center }
	, m_Width{ width }
	, m_Height{ height }
	, m_Speed{ 150.0f }
	, m_Boundaries{ Rectf{0, 0, 0, 0} }
	, m_Bullet{ 10.0f, 15.0f }
{
}

void Avatar::Draw() const
{
	m_Bullet.Draw();
	utils::SetColor(Color4f{ 1.0f, 0.5f, 0.0f, 1.0f });
	utils::DrawRect(m_Center.x - m_Width / 2.0f, m_Center.y - m_Height / 2.0f, m_Width, m_Height, 3.0f);
}

void Avatar::Update(float elapsedSec, Enemy* pEnemies, int numEnemies)
{
	m_Bullet.Update(elapsedSec, pEnemies, numEnemies);
	HandleMoveKeysState(elapsedSec);
	Clamp();
}

void Avatar::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Avatar::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Avatar::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;

	m_Bullet.SetBoundaries(boundaries);
}

void Avatar::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		m_Bullet.Shoot(
			m_Center,
			Vector2f{
				0.0f,
				10.0f
			}
		);
		break;
	}
}

void Avatar::Clamp()
{
	if (m_Boundaries.left > m_Center.x - m_Width / 2.0f)
		m_Center.x = m_Boundaries.left + m_Width / 2.0f;
	if (m_Boundaries.left + m_Boundaries.width <= m_Center.x + m_Width / 2.0f)
		m_Center.x = m_Boundaries.left + m_Boundaries.width - m_Width / 2.0f;

}

void Avatar::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Center.x += m_Speed * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Center.x -= m_Speed * elapsedSec;
	}
}
