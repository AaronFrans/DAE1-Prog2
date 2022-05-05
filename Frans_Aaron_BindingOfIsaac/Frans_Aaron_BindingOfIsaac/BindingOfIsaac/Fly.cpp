#include "pch.h"
#include "Fly.h"
#include "Sprite.h"
#include "Room.h"
#include "utils.h"
#include "Isaac.h"

Fly::Fly(Texture* movementSpriteSheet, Texture* DyingSpriteSheet, Point2f centerPoint)
	: Enemy{ centerPoint, 0.5f, 75, 5 }
	, m_State{ FlyState::moving }
	, m_DyingAccuSec{ 0 }
{
	m_pMovementSprite = new Sprite{ movementSpriteSheet, 3, 1, 1 / 15.0f, 1 };
	m_MovementWidth = m_pMovementSprite->GetFrameWidth();
	m_MovementHeight = m_pMovementSprite->GetFrameHeight();

	m_pDyingSprite = new Sprite{ DyingSpriteSheet, 4, 3, 1 / 15.0f, 1, 11 };
	m_DyingWidth = m_pDyingSprite->GetFrameWidth();
	m_DyingHeight = m_pDyingSprite->GetFrameHeight();
	m_DyingMaxSec = m_pDyingSprite->GetTotalLoopTime();
}

Fly::Fly(const Fly& rhs)
	: Enemy{ rhs.m_CenterPosition , 0.5f, 100, 5 }
	, m_State{ rhs.m_State }
	, m_DyingAccuSec{ 0 }
{
	m_pMovementSprite = new Sprite{ *rhs.m_pMovementSprite };
	m_MovementWidth = rhs.m_MovementWidth;
	m_MovementHeight = rhs.m_MovementHeight;

	m_pDyingSprite = new Sprite{ *rhs.m_pDyingSprite };
	m_DyingWidth = rhs.m_DyingWidth;
	m_DyingHeight = rhs.m_DyingHeight;
	m_DyingMaxSec = rhs.m_DyingMaxSec;
}

Fly& Fly::operator=(const Fly& rhs)
{
	m_CenterPosition = rhs.m_CenterPosition;
	m_Damage = rhs.m_Damage;
	m_Speed = rhs.m_Speed;
	m_Health =rhs.m_Health;

	m_State = rhs.m_State ;
	m_DyingAccuSec = rhs.m_DyingAccuSec;

	m_pMovementSprite = new Sprite{ *rhs.m_pMovementSprite };
	m_MovementWidth = rhs.m_MovementWidth;
	m_MovementHeight = rhs.m_MovementHeight;

	m_pDyingSprite = new Sprite{ *rhs.m_pDyingSprite };
	m_DyingWidth = rhs.m_DyingWidth;
	m_DyingHeight = rhs.m_DyingHeight;
	m_DyingMaxSec = rhs.m_DyingMaxSec;

	return *this;
}

Fly::~Fly()
{
	delete m_pMovementSprite;
	m_pMovementSprite = nullptr;
	delete m_pDyingSprite;
	m_pDyingSprite = nullptr;
}

void Fly::Draw() const
{
	switch (m_State)
	{
	case FlyState::moving:
		m_pMovementSprite->Draw(Rectf{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f,
			m_MovementWidth, m_MovementHeight });
		break;
	case FlyState::dying:
		m_pDyingSprite->Draw(Rectf{ m_CenterPosition.x - m_DyingWidth / 2.0f,m_CenterPosition.y - m_DyingHeight / 2.0f,
			m_DyingWidth, m_DyingHeight });
		break;
	}
}

void Fly::Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex)
{
	switch (m_State)
	{
	case FlyState::moving:
		m_pMovementSprite->Update(elapsedSec);
		DoEnemyCollisions(currentRoom->GetEnemies(), currentEnemyIndex);
		UpdatePos(elapsedSec, currentRoom, isaac);
		break;
	case FlyState::dying:
		DoDying(elapsedSec);
		break;
	}
}

bool Fly::IsDead() const
{
	return m_State == FlyState::dying || m_State == FlyState::dead;
}

Circlef Fly::GetHitBox() const
{
	return Circlef{ m_CenterPosition, m_MovementHeight / 2.0f};
}

void Fly::TakeDamage(float damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_State = FlyState::dying;
	}
}

Enemy* Fly::clone() const
{
	return new Fly(*this);
}

void Fly::UpdatePos(float elapsedSec, const Room* currentRoom, Isaac* isaac)
{
	Vector2f direction{ m_CenterPosition, isaac->GetCenter() };

	direction = direction.Normalized();
	m_Velocity = direction * m_Speed;
	m_CenterPosition += m_Velocity * elapsedSec;
	DoRoomCollision(currentRoom);
	DoIsaacCollisionCheck(isaac);
}

void Fly::DoIsaacCollisionCheck(Isaac* isaac)
{
	if (utils::IsOverlapping(isaac->GetHitBox(), GetHitBox()))
	{
		isaac->TakeDamage(m_Damage);
	}
}

void Fly::DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex)
{
	Circlef hitbox = GetHitBox();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if ((i != currentEnemyIndex &&
			!enemies[i]->IsDead()))
		{
			Point2f otherCenter{ enemies[i]->GetCenter() };
			Vector2f currentToEnemy{ m_CenterPosition ,otherCenter };
			Vector2f velNorm{ m_Velocity.Normalized() };
			float dot{ velNorm.DotProduct(currentToEnemy) };
			if (dot > 0)
			{
				Circlef enemyHitbox{ enemies[i]->GetHitBox() };
				if (utils::IsOverlapping(hitbox, enemyHitbox))
				{

					float radiusSum{ enemyHitbox.radius + hitbox.radius };
					Vector2f enemyToCurrentNorm{ -(currentToEnemy.Normalized()) };
					Vector2f currentDisplament{ enemyToCurrentNorm * radiusSum };
					m_CenterPosition = otherCenter + currentDisplament;

					if (typeid(*this) != typeid(*enemies[i]))
					{
						if (abs(currentToEnemy.x) > abs(currentToEnemy.y))
						{
							if (currentToEnemy.x > 0)
								m_Velocity.x += 2;
							else
								m_Velocity.x -= 2;
						}
						else if (abs(currentToEnemy.x) < abs(currentToEnemy.y))
						{
							if (currentToEnemy.y > 0)
								m_Velocity.y += 2;
							else
								m_Velocity.y -= 2;
						}
					}
					
				}
			}

		}
	}
}

void Fly::DoDying(float elapsedSec)
{
	m_DyingAccuSec += elapsedSec;
	if (m_DyingAccuSec >= m_DyingMaxSec)
		m_State = FlyState::dead;
	else
	m_pDyingSprite->Update(elapsedSec);

}
