#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include "utils.h"

Avatar::Avatar()
	: m_HorSpeed{ 200.0f }
	, m_JumpSpeed{ 600.0f }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_Velocity{ 0.0f, 0.0f }
	, m_Shape{ 50, 280, 36, 97 }
	, m_ActionState{ ActionState::moving }
	, m_AccuTransformSec{ 0.0f }
	, m_MaxTransformSec{ 1.0f }
	, m_Power{ 0 }
{
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	if (m_ActionState == ActionState::transforming)
	{

		if (m_AccuTransformSec >= m_MaxTransformSec)
		{

			m_ActionState = ActionState::waiting;
			m_AccuTransformSec = 0;

		}
		m_AccuTransformSec += elapsedSec;

	}
	else
	{
		bool isOnGround{ level.IsOnGround(m_Shape) };
		if (!isOnGround)
		{
			UpdatePos(elapsedSec, isOnGround, level);
		}
		else
		{
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);
			if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_RIGHT])
				UpdatePos(elapsedSec, isOnGround, level);
			else
				m_ActionState = ActionState::waiting;

		}
	}

}

void Avatar::Draw() const
{
	utils::FillRect(m_Shape);
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape()
{
	return m_Shape;
}

void Avatar::HandleCollision(const Level& level)
{
	level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::UpdatePos(float elapsedSec, bool isOnGround, const Level& level)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	switch (isOnGround)
	{
	case true:
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_Shape.left -= m_HorSpeed * elapsedSec;
		}
		else if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_Shape.left += m_HorSpeed * elapsedSec;
		}
		else if (pStates[SDL_SCANCODE_UP])
		{
			m_Velocity.y += m_JumpSpeed;
		}
	case false:
		m_Velocity.y += m_Acceleration.y * elapsedSec;
		m_Shape.bottom += m_Velocity.y * elapsedSec;
		break;
	}

	HandleCollision(level);

}



