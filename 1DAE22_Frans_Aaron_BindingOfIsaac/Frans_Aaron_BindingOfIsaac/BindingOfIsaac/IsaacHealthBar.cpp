#include "pch.h"
#include "IsaacHealthBar.h"
#include "Texture.h"
#include "Hearth.h"

IsaacHealthBar::IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft)
	: m_Health{ health }
	, m_HeartSize{ 20 }
{
	for (int i = 0; i < m_Health; i++)
	{
		m_pHearts.push_back(new Hearth(heartSheet,
			Hearth::HearthState::full,
			m_HeartSize));
	}
}

IsaacHealthBar::~IsaacHealthBar()
{
	for (Hearth* hearth : m_pHearts)
	{
		delete hearth;
	}
}

void IsaacHealthBar::DrawHealtBar(const Rectf& Camera) const
{
	for (int i = 0; i < m_pHearts.size(); i++)
	{
		m_pHearts[i]->Draw(Point2f{
			Camera.left + m_HeartSize / 2.0f + m_HeartSize * i,
			(Camera.bottom + Camera.height) - m_HeartSize / 2.0f });
	}
}


