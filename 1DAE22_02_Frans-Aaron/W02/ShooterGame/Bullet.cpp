#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "Enemy.h"

Bullet::Bullet()
	: Bullet(0, 0)
{
}

Bullet::Bullet(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_IsActivated{ false }
{
}

void Bullet::Draw() const
{
	if (m_IsActivated)
	{
		utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
		utils::FillRect(m_Center.x - m_Width / 2.0f, m_Center.y - m_Height / 2.0f, m_Width, m_Height);
	}
}

void Bullet::Update(float elapsedSec, Enemy* pEnemies, int numEnemies)
{
	if (m_IsActivated)
	{
		m_Center.y += m_Velocity.y;
		CheckBoundaries();
		CheckEnemiesHit(pEnemies, numEnemies);
	}
}

void Bullet::Shoot(const Point2f& center, const Vector2f& velocity)
{
	if (!m_IsActivated)
	{
		m_IsActivated = true;
		m_Center = center;
		m_Velocity = velocity;
	}
}

void Bullet::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Bullet::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Bullet::CheckBoundaries()
{
	if (m_Center.y - m_Height / 2.0f > m_Boundaries.height)
		m_IsActivated = false;
}

void Bullet::CheckEnemiesHit(Enemy* pEnemies, int numEnemies)
{
	for (int i = 0; i < numEnemies; i++)
	{
		if (!pEnemies[i].IsDead())
		{
			if (pEnemies[i].DoHitTest(Rectf{
				m_Center.x - m_Width / 2.0f,
				m_Center.y - m_Height / 2.0f,
				m_Width,
				m_Height
				}))
			{
				m_IsActivated = false;
			}
		}

	}
}
