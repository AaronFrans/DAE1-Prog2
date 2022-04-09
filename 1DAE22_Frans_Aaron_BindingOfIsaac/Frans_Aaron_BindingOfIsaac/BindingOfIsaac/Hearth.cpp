#include "pch.h"
#include "Hearth.h"
#include "Texture.h"

Hearth::Hearth(Texture* heartSheet, HearthState state, float dstHeartSize)
	: m_State{ state }
	, m_DstHeartSize{ dstHeartSize }
{
	m_pHeartSheet = heartSheet;
	m_SrcHeartSize = m_pHeartSheet->GetWidth() / 3;
}

void Hearth::Draw(const Point2f& centerPos) const
{
	Rectf srcRect{ m_SrcHeartSize * (int)m_State, 0, m_SrcHeartSize, m_SrcHeartSize };
	Rectf dstRect{ centerPos.x - m_DstHeartSize / 2.0f, centerPos.y - m_DstHeartSize / 2.0f, m_DstHeartSize, m_DstHeartSize };

	m_pHeartSheet->Draw(dstRect, srcRect);
}
