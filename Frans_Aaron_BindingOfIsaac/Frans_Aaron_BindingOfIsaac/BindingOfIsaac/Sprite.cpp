#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>


Sprite::Sprite()
	: Sprite(nullptr, 0, 0, 0, 0, 0)
{
}

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

Sprite::Sprite(const Sprite& rhs)
	: m_pSpriteSheet{ rhs.m_pSpriteSheet }
	, m_Frames{ rhs.m_Frames }
	, m_Cols{ rhs.m_Cols }
	, m_Rows{ rhs.m_Rows }
	, m_FrameSec{ rhs.m_FrameSec }
	, m_ActFrame{ 0 }
	, m_AccuSec{ 0.0f }
	, m_Scale{ rhs.m_Scale }
{
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
	m_pSpriteSheet = rhs.m_pSpriteSheet;
	m_Frames = rhs.m_Frames;
	m_Cols = rhs.m_Cols;
	m_Rows = rhs.m_Rows;
	m_FrameSec = rhs.m_FrameSec;
	m_Scale = rhs.m_Scale;

	return *this;
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

void Sprite::Draw(const Point2f& pos, const Point2f& srcBottomLeft) const
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

void Sprite::Draw(const Rectf& dstRect, const Point2f& srcBottomLeft) const
{
	const float frameWidth{ GetFrameWidth() },
		frameHeight{ GetFrameHeight() };


	Rectf srcRect{ srcBottomLeft.x + m_ActFrame % m_Cols * frameWidth,
				   srcBottomLeft.y + (m_ActFrame / m_Cols + 1) * frameHeight,
				   frameWidth,
				   frameHeight };

	m_pSpriteSheet->Draw(dstRect, srcRect);
}

float Sprite::GetFrameWidth() const
{
	return this->m_pSpriteSheet->GetWidth() / m_Cols;
}

float Sprite::GetFrameHeight() const
{
	return this->m_pSpriteSheet->GetHeight() / m_Rows;
}

int Sprite::GetNrFrames() const
{
	return m_Frames;
}

void Sprite::SetActFrame(int actFrame)
{
	m_ActFrame = actFrame;
}

void Sprite::SetAccuSec(float accuSec)
{
	m_AccuSec = accuSec;
}

void Sprite::SetFrameSec(float frameSec)
{
	m_FrameSec = frameSec;
}

float Sprite::GetTotalLoopTime()
{
	return m_FrameSec * m_Frames;
}
