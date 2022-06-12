#include "pch.h"
#include "IsaacHealthBar.h"
#include "Texture.h"
#include "Hearth.h"
#include "utils.h"

IsaacHealthBar::IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft)
	: m_Health{ health }
	, m_HeartSize{ 20 }
	, m_MaxHealth{ health }
{
	m_pEmptyHeart = new Hearth{ heartSheet,
		Hearth::HearthState::empty,
		m_HeartSize };

	for (int i = 0; i < m_Health; i++)
	{
		m_pHearts.push_back(new Hearth{ heartSheet,
			Hearth::HearthState::full,
			m_HeartSize });
	}
}

IsaacHealthBar::~IsaacHealthBar()
{
	for (Hearth* hearth : m_pHearts)
	{
		delete hearth;
	}

	delete m_pEmptyHeart;
}

void IsaacHealthBar::DrawHealtBar(const Rectf& Camera, float offsetWidth) const
{
	for (int i = 0; i < m_pHearts.size(); i++)
	{
		m_pHearts[i]->Draw(Point2f{
			Camera.left + offsetWidth + m_HeartSize / 2.0f + m_HeartSize * i,
			(Camera.bottom + Camera.height - 20) - m_HeartSize / 2.0f });
	}
}


void IsaacHealthBar::TakeDamage(float damage)
{
	size_t index{ m_pHearts.size() - 1 };
	while (m_pHearts[index]->GetState() == Hearth::HearthState::empty)
	{
		index--;
	}
	m_pHearts[index]->TakeDamage(damage);
	m_Health -= damage;
}

bool IsaacHealthBar::IsDead()
{
	return m_Health <= 0;
}

bool IsaacHealthBar::IsFull()
{
	return m_Health == m_MaxHealth;
}

void IsaacHealthBar::AddHealth(float amount)
{
	for (int i = 0; i < amount; i++)
	{
		m_pHearts.push_back(new Hearth{ *m_pEmptyHeart });
		m_Health += 1;
	}
}

void IsaacHealthBar::Heal(float healAmount)
{
	size_t index{ 0 };
	while (m_pHearts[index]->GetState() == Hearth::HearthState::full)
	{
		index++;
	}
	float rest{ m_pHearts[index]->Heal(healAmount) };
	if (utils::IsEqual(0.5f, rest, 0.0000001f))
	{
		index++;
		if (index < m_pHearts.size())
		{
			m_pHearts[index]->Heal(rest);
		}

	}
	m_Health += healAmount;
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}


