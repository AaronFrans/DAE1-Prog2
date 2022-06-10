#include "pch.h"
#include "BossHealthBar.h"
#include "Texture.h"


BossHealthBar::BossHealthBar(Texture* healthBar, float health)
	: m_pHealthBar{ healthBar }
	, m_Health{ health }
	, m_MaxHealth{ health }
{

	m_SrcWidth = m_pHealthBar->GetWidth();
	m_SrcHeight = m_pHealthBar->GetHeight() / 2.0f;
}

BossHealthBar::BossHealthBar(const BossHealthBar& rhs)
	: m_pHealthBar{ rhs.m_pHealthBar }
	, m_Health{ rhs.m_Health }
	, m_MaxHealth{ rhs.m_MaxHealth }
	, m_SrcWidth{ rhs.m_SrcWidth }
	, m_SrcHeight{ rhs.m_SrcHeight }
{
}

BossHealthBar& BossHealthBar::operator=(const BossHealthBar& rhs)
{
	m_pHealthBar = rhs.m_pHealthBar;
	m_Health = rhs.m_Health;
	m_MaxHealth = rhs.m_MaxHealth;
	m_SrcWidth = rhs.m_SrcWidth;
	m_SrcHeight = rhs.m_SrcHeight;
	return *this;
}

void BossHealthBar::DrawHealtBar(const Rectf& Camera) const
{
	Point2f drawBottomLeft{
		Camera.left + (Camera.width / 2.0f) - m_SrcWidth / 2.0f,
		Camera.bottom + (Camera.height - m_SrcHeight)
	};

	//draw empty
	Rectf srcRect{
		0,
		0,
		m_SrcWidth,
		m_SrcHeight
	};
	m_pHealthBar->Draw(drawBottomLeft, srcRect);

	//draw filled
	float healthPercentage{ m_Health / m_MaxHealth };
	srcRect.width = m_SrcWidth * healthPercentage;
	srcRect.bottom = m_SrcHeight;
	m_pHealthBar->Draw(drawBottomLeft, srcRect);

}


void BossHealthBar::TakeDamage(float damage)
{
	m_Health -= damage;
	if (m_Health < 0)
	{
		m_Health = 0;
	}
}
