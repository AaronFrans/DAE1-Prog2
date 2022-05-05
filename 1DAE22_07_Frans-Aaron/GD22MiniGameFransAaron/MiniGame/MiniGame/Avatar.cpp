#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include "utils.h"
#include "Texture.h"

Avatar::Avatar()
	: m_HorSpeed{ 200.0f }
	, m_JumpSpeed{ 600.0f }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_Velocity{ 0.0f, 0.0f }
	, m_Shape{ 50, 280, 72, 97 }
	, m_ActionState{ ActionState::moving }
	, m_AccuTransformSec{ 0.0f }
	, m_MaxTransformSec{ 1.0f }
	, m_Power{ 0 }
	, m_ClipHeight{ 97.0f }
	, m_ClipWidth{ 72.0f }
	, m_NrOfFrames{ 10 }
	, m_NrOfFramesPerSec{ 10 }
	, m_AnimTime{ 0 }
	, m_AnimFrame{ 0 }
{

	m_pSpritesTexture = new Texture{ "Resources/Images/AvatarSheet.png" };
}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
	m_pSpritesTexture = nullptr;
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	UpdateCurrentFrame(elapsedSec);
	if (m_ActionState == ActionState::transforming)
	{

		if (m_AccuTransformSec >= m_MaxTransformSec)
		{
			m_Power++;
			m_ActionState = ActionState::waiting;
			m_AccuTransformSec = 0;
			m_AnimTime = 0;
			m_AnimFrame = 0;
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
			{
				if (m_ActionState != ActionState::waiting)
				{
					m_ActionState = ActionState::waiting;
					m_AnimTime = 0;
					m_AnimFrame = 0;
				}
			}

		}
	}


}

void Avatar::Draw() const
{
	float textureHeight{ m_pSpritesTexture->GetHeight() };
	float dstLeft{ m_ClipWidth * m_AnimFrame };
	float pow{ ((m_ClipHeight * 3) * m_Power) };
	float act{ (m_ClipHeight * ((int)m_ActionState + 1)) };
	float dstBottom{ pow + act };
	Rectf dstRect{ dstLeft, dstBottom,m_ClipWidth, m_ClipHeight };
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_LEFT])
	{
		glPushMatrix();
		glTranslatef(m_Shape.left + m_Shape.width/2.0f, m_Shape.height, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-(m_Shape.left + m_Shape.width / 2.0f), -m_Shape.height, 0);
		m_pSpritesTexture->Draw(m_Shape, dstRect);
		glPopMatrix();
	}
	else
		m_pSpritesTexture->Draw(m_Shape, dstRect);

}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
	m_AnimTime = 0;
	m_AnimFrame = 0;
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
	if (m_ActionState != ActionState::moving)
	{
		m_ActionState = ActionState::moving;
		m_AnimTime = 0;
		m_AnimFrame = 0;
	}
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

void Avatar::UpdateCurrentFrame(float elapsedSec)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
	{
		m_AnimTime -= 1.0f / m_NrOfFramesPerSec;
		m_AnimFrame++;
		if (m_AnimFrame % 10 == m_NrOfFrames)
			m_AnimFrame = 0;
	}
}



