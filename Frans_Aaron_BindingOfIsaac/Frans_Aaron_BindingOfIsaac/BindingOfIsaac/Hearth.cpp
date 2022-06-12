#include "pch.h"
#include "Hearth.h"
#include "Texture.h"
#include "utils.h"

Hearth::Hearth(Texture* heartSheet, HearthState state, float dstHeartSize)
	: m_State{ state }
	, m_DstHeartSize{ dstHeartSize }
{
	m_pHeartSheet = heartSheet;
	m_SrcHeartSize = m_pHeartSheet->GetWidth() / 3;
}

Hearth::Hearth(const Hearth& rhs)
	: m_State{ rhs.m_State }
	, m_DstHeartSize{ rhs.m_DstHeartSize }
{
	m_pHeartSheet = rhs.m_pHeartSheet;
	m_SrcHeartSize = rhs.m_SrcHeartSize;
}

Hearth& Hearth::operator=(const Hearth& rhs)
{
	m_State = rhs.m_State;
	m_DstHeartSize = rhs.m_DstHeartSize;
	m_pHeartSheet = rhs.m_pHeartSheet;
	m_SrcHeartSize = rhs.m_SrcHeartSize;

	return *this;
}

void Hearth::Draw(const Point2f& centerPos) const
{
	Rectf srcRect{ m_SrcHeartSize * (int)m_State, 0, m_SrcHeartSize, m_SrcHeartSize };
	Rectf dstRect{ centerPos.x - m_DstHeartSize / 2.0f, centerPos.y - m_DstHeartSize / 2.0f, m_DstHeartSize, m_DstHeartSize };

	m_pHeartSheet->Draw(dstRect, srcRect);
}

Hearth::HearthState Hearth::GetState() const
{
	return m_State;
}

void Hearth::TakeDamage(float damage)
{
	if (utils::IsEqual(damage, 0.5f, 0.000001f))
	{
		if (m_State == HearthState::full)
		{
			m_State = HearthState::half;
		}
		else if (m_State == HearthState::half)
		{
			m_State = HearthState::empty;
		}
	}
	else if (utils::IsEqual(damage, 1.0f, 0.000001f))
	{
		m_State = HearthState::empty;
	}
	else
	{
		std::cout << "Damage value is not compatible";
	}
}

float Hearth::Heal(float healAmount)
{
	if (utils::IsEqual(healAmount, 0.5f, 0.000001f))
	{
		if (m_State == HearthState::empty)
		{
			m_State = HearthState::half;
		}
		else if (m_State == HearthState::half)
		{
			m_State = HearthState::full;
		}
	}
	else if (utils::IsEqual(healAmount, 1.0f, 0.000001f))
	{
		if (m_State == HearthState::half)
		{
			m_State = HearthState::full;
			return 0.5f;
		}
		else if (m_State == HearthState::empty)
		{
			m_State = HearthState::full;
			return 0;
		}

	}
	else
	{
		std::cout << "Heal value is not compatible";
	}
	return 0.f;
}
