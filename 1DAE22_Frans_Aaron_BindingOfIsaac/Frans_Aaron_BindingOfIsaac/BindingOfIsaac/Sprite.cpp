#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>


Sprite::Sprite(Texture* texture, int nrCols, int nrRows, float frameSec, float scale, int nrFrames)
	: m_pSpriteSheet{ texture }
	, m_Frames{ nrFrames }
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_FrameSec{ frameSec }
	, m_ActFrame{ 0 }
	, m_AccuSec{ 0.0f }
	, m_Scale{ scale }
{
	if (nrFrames == 0)
		m_Frames = m_Cols * m_Rows;
}

Sprite::~Sprite()
{
}

void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		m_ActFrame++;
		if (m_ActFrame % m_Frames == 0)
		{
			m_ActFrame = 0;
		}
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw(const Point2f& pos, const Point2f& srcBottomLeft)
{
	const float frameWidth{ GetFrameWidth() },
		frameHeight{ GetFrameHeight() };


	Rectf srcRect{ srcBottomLeft.x + m_ActFrame % m_Cols * frameWidth,
				   srcBottomLeft.y + (m_ActFrame / m_Rows + 1) * frameHeight,
				   frameWidth,
				   frameHeight };
	Rectf dstRect{ pos.x ,
				   pos.y,
				   srcRect.width,
				   srcRect.height };

	m_pSpriteSheet->Draw(dstRect, srcRect);
}

float Sprite::GetFrameWidth()
{
	return this->m_pSpriteSheet->GetWidth() / m_Cols;
}

float Sprite::GetFrameHeight()
{
	return this->m_pSpriteSheet->GetHeight() / m_Rows;
}

void Sprite::SetActFrame(int actFrame)
{
	m_ActFrame = actFrame;
}

void Sprite::SetAccuSec(float accuSec)
{
	m_AccuSec = accuSec;
}
