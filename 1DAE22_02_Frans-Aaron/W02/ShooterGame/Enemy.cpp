#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy()
	: Enemy{ Point2f{0,0}, 0,0 }
{
}

Enemy::Enemy(const Point2f& center, float width, float height)
	: m_Center{ center }
	, m_Width{ width }
	, m_Height{ height }
	, m_IsDead{ false }
{
}

void Enemy::Draw() const
{

	if (!IsDead())
	{
		utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
		utils::DrawRect(m_Center.x - m_Width / 2.0f, m_Center.y - m_Height / 2.0f, m_Width, m_Height, 3.0f);
	}

}

void Enemy::SetSenter(const Point2f& center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	m_Height = height;
	m_Width = width;
}

bool Enemy::DoHitTest(const Rectf& other)
{
	bool isHit{ utils::IsOverlapping(Rectf{ m_Center.x - m_Width / 2.0f,
		m_Center.y - m_Height / 2.0f,
		m_Width,
		m_Height },
		other) };
	std::cout << "Dead: " << (bool)isHit << '\n';
	if (isHit)
		m_IsDead = true;
	return isHit;
}

bool Enemy::IsDead() const
{
	return m_IsDead;
}
