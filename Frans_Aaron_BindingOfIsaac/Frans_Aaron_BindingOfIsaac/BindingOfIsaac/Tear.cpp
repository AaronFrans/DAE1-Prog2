#include "pch.h"
#include "Tear.h"
#include "Sprite.h"
#include "Texture.h"
#include "utils.h"
#include "Poop.h"
#include "Enemy.h"
#include <vector>
#include <typeinfo>

Tear::Tear()
	: m_State{ TearState::inactive }
	, m_Height{ 0 }
	, m_pTearTexture{ nullptr }
	, m_AccuGroundTime{ 0 }
	, m_TotalGroundTime{ 0 }
	, m_HeightDecrease{ 35 }
	, m_TearRadius{ 0 }
	, m_IsFront{ false }
	, m_Damage{ 0 }
{
	m_pTearHitSprite = nullptr;
	m_pTearTexture = nullptr;
}

Tear::~Tear()
{
	delete m_pTearHitSprite;
	m_pTearHitSprite = nullptr;
}

void Tear::Draw() const
{
	if (m_State == TearState::hit)
	{
		m_pTearHitSprite->Draw(Rectf{ m_Center.x - (m_TearRadius * 3.0f),
			m_Center.y + m_Height - (m_TearRadius * 3.0f),
			(m_TearRadius * 6.0f),
			(m_TearRadius * 6.0f)
			});
	}
	else
	{
		m_pTearTexture->Draw(Rectf{ m_Center.x - m_TearRadius,
			m_Center.y + m_Height - m_TearRadius,
			m_TearRadius * 2,
			m_TearRadius * 2 });
	}

}

void Tear::Update(float elapsedSec, std::vector<GameObject*> gameObjects, std::vector<Enemy*> enemies)
{

	if (m_State == TearState::hit)
	{
		m_AccuGroundTime += elapsedSec;
		if (m_AccuGroundTime >= m_TotalGroundTime)
		{
			ClearTear();
		}
		else
		{

			m_pTearHitSprite->Update(elapsedSec);
		}
	}
	else
	{

		m_Center.x += m_Velocity.x * elapsedSec;
		m_Center.y += m_Velocity.y * elapsedSec;
		if (!utils::IsPointInRect(m_Center, m_TearRange))
		{
			m_Height -= m_HeightDecrease * elapsedSec;
			if (m_Height <= 0)
				m_State = TearState::hit;
		}
		Circlef shape{ Point2f{m_Center.x, m_Center.y + m_Height}, m_TearRadius };
		for (Enemy* enemy : enemies)
		{
			if (utils::IsOverlapping(enemy->GetHitBox(), shape) && m_State == TearState::active)
			{
				if (!enemy->IsDead())
				{
					m_State = TearState::hit;
					enemy->TakeDamage(m_Damage);
				}
			}
		}
		for (GameObject* object : gameObjects)
		{
			if (utils::IsOverlapping(object->GetShape(), shape) && m_State == TearState::active)
			{
				if (object->IsNotDestroyed())
				{
					if (typeid(*object) == typeid(Poop))
					{
						Poop* pPoop{ static_cast<Poop*> (object) };

						pPoop->IsHit();
					}
						m_State = TearState::hit;
				}
			}
		}

	}

}

Tear::TearState Tear::GetState() const
{
	return m_State;
}

bool Tear::GetIsFront() const
{
	return m_IsFront;
}

void Tear::SetState(TearState state)
{
	m_State = state;
}

void Tear::SetVelocity(Vector2f velocity)
{
	m_Velocity = velocity;
}

void Tear::SetTearShape(Point2f center, float tearRadius)
{
	m_TearRadius = tearRadius;
	m_Center = center;
}

void Tear::SetHeight(float height)
{
	m_Height = height;
}

void Tear::SetTearTexture(Texture* tearTexture)
{
	m_pTearTexture = tearTexture;
}

void Tear::SetTearHitSprite(Texture* tearHitTexture)
{
	m_pTearHitSprite = new Sprite(tearHitTexture, 4, 4, 1 / 20.0f, 1, 15);
	m_TotalGroundTime = m_pTearHitSprite->GetTotalLoopTime();
}

void Tear::SetRange(float range)
{
	m_TearRange = Rectf{ m_Center.x - range / 2.0f,
		m_Center.y - range / 2.0f,
		 range,
		 range
	};
}

void Tear::SetIsFront(bool isFront)
{
	m_IsFront = isFront;
}

void Tear::SetDamage(float damage)
{
	m_Damage = damage;
}

void Tear::ClearTear()
{
	delete m_pTearHitSprite;
	m_pTearHitSprite = nullptr;
	m_pTearTexture = nullptr;
	m_TotalGroundTime = 0;
	m_AccuGroundTime = 0;
	m_State = TearState::inactive;
}
