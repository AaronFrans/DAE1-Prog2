#include "pch.h"
#include "SmallSpider.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Room.h"
#include "GameObject.h"
#include "utils.h"
#include "Isaac.h"

SmallSpider::SmallSpider(Texture* movementSpriteSheet, Texture* deathSpriteSheet, Point2f centerPoint, float damage, float speed)
	: Enemy{ centerPoint, damage, speed }
	, m_State{ SmallSpiderState::idle }
	, m_MovementAccuSec{ 0 }
	, m_IdleAccuSec{ 0 }
	, m_IdleMinSec{ 0.5 }
{
	m_pMovementSprite = new Sprite(movementSpriteSheet, 2, 4, 1 / 10.0f, 1);
	m_MovementWidth = m_pMovementSprite->GetFrameWidth();
	m_MovementHeight = m_pMovementSprite->GetFrameHeight();


	m_MovementMaxSec = m_pMovementSprite->GetTotalLoopTime();

	m_pDeathSprite = new Sprite(movementSpriteSheet, 4, 3, 1 / 10.0f, 1, 11);
	m_DeathWidth = m_pDeathSprite->GetFrameWidth();
	m_DeathHeight = m_pDeathSprite->GetFrameHeight();
}

SmallSpider::~SmallSpider()
{
	delete m_pMovementSprite;
	m_pMovementSprite = nullptr;
	delete m_pDeathSprite;
	m_pDeathSprite = nullptr;

}

void SmallSpider::Draw() const
{
	switch (m_State)
	{
	case SmallSpider::SmallSpiderState::idle:
		m_pMovementSprite->Draw(Rectf{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f,
			m_MovementWidth, m_MovementHeight });
		break;
	case SmallSpider::SmallSpiderState::moving:
		m_pMovementSprite->Draw(Rectf{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f,
			m_MovementWidth, m_MovementHeight });
		break;
	case SmallSpider::SmallSpiderState::dying:
		m_pDeathSprite->Draw(Rectf{ m_CenterPosition.x - m_DeathWidth / 2.0f,m_CenterPosition.y - m_DeathHeight / 2.0f,
			m_DeathWidth, m_DeathHeight });
		break;
	default:
		break;
	}

}

void SmallSpider::Update(float elapsedSec, const Room* currentRoom, Isaac* isaac)
{
	switch (m_State)
	{
	case SmallSpider::SmallSpiderState::idle:
		m_pMovementSprite->SetAccuSec(0);
		m_pMovementSprite->SetActFrame(0);
		m_Velocity = Vector2f{ 0, 0 };
		DoIdle(elapsedSec);
		break;
	case SmallSpider::SmallSpiderState::moving:
		m_pMovementSprite->Update(elapsedSec);
		if (m_Velocity == Vector2f{ 0,0 })
		{
			m_Velocity.x += utils::GetRand(-m_Speed, m_Speed, 2);
			m_Velocity.y += utils::GetRand(-m_Speed, m_Speed, 2);
		}
		UpdatePos(elapsedSec, currentRoom);
		DoIsaacCollisionCheck(isaac);
		break;
	case SmallSpider::SmallSpiderState::dying:
		break;
	default:
		break;
	}
}

bool SmallSpider::IsDead() const
{
	return m_HasDied;
}

void SmallSpider::UpdatePos(float elapsedSec, const Room* currentRoom)
{
	m_MovementAccuSec += elapsedSec;
	if (m_MovementAccuSec <= m_MovementMaxSec)
	{
		m_CenterPosition += m_Velocity * elapsedSec;
		DoRoomCollision(currentRoom);
		DoGameObjectCollision(currentRoom->GetGameObjects());
	}
	else
	{
		m_MovementAccuSec = 0;
		m_State = SmallSpiderState::idle;
	}
}

void SmallSpider::DoIdle(float elapsedSec)
{
	m_IdleAccuSec += elapsedSec;
	if (m_IdleAccuSec >= m_IdleMinSec)
	{
		if (utils::GetRand(0, 1) == 0)
		{
			m_IdleAccuSec = 0;
			m_State = SmallSpiderState::moving;
		}
	}

}

void SmallSpider::DoRoomCollision(const Room* currentRoom)
{
	utils::HitInfo hitInfo;
	Point2f spiderHitboxBottom{ m_CenterPosition.x,  m_CenterPosition.y - m_MovementHeight / 2.0f };
	Point2f spiderHitboxTop{ m_CenterPosition.x,  m_CenterPosition.y + m_MovementHeight / 2.0f };
	Point2f spiderHitboxLeft{ m_CenterPosition.x - m_MovementWidth / 2.0f,  m_CenterPosition.y };
	Point2f spiderHitboxRight{ m_CenterPosition.x + m_MovementWidth / 2.0f,  m_CenterPosition.y };
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), spiderHitboxTop, spiderHitboxBottom, hitInfo))
	{
		if (m_Velocity.y > 0)
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y - m_MovementHeight / 2.0f;
			m_Velocity.y = -m_Velocity.y;
		}
		else
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y + m_MovementHeight / 2.0f;
			m_Velocity.y = -m_Velocity.y;
		}
	}
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), spiderHitboxLeft, spiderHitboxRight, hitInfo))
	{
		if (m_Velocity.x > 0)
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x - m_MovementWidth / 2.0f;
			m_Velocity.x = -m_Velocity.y;
		}
		else
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x + m_MovementWidth / 2.0f;
			m_Velocity.x = -m_Velocity.y;
		}
	}
}

void SmallSpider::DoGameObjectCollision(const std::vector<GameObject*>& objects)
{
	utils::HitInfo hitInfo;
	Point2f spiderHitboxBottom{ m_CenterPosition.x,  m_CenterPosition.y - m_MovementHeight / 2.0f };
	Point2f spiderHitboxTop{ m_CenterPosition.x,  m_CenterPosition.y + m_MovementHeight / 2.0f };
	Point2f spiderHitboxLeft{ m_CenterPosition.x - m_MovementWidth / 2.0f,  m_CenterPosition.y };
	Point2f spiderHitboxRight{ m_CenterPosition.x + m_MovementWidth / 2.0f,  m_CenterPosition.y };
	for (GameObject* object : objects)
	{
		if (object->IsNotDestroyed())
		{
			std::vector<Point2f> vertices{ utils::GetVertices(object->GetShape()) };
			if (utils::Raycast(vertices, spiderHitboxTop, spiderHitboxBottom, hitInfo))
			{
				if (m_Velocity.y > 0)
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y - m_MovementHeight / 2.0f;
				}
				else
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y + m_MovementHeight / 2.0f;
				}
			}
			if (utils::Raycast(vertices, spiderHitboxLeft, spiderHitboxRight, hitInfo))
			{
				if (m_Velocity.x > 0)
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x - m_MovementWidth / 2.0f;
				}
				else
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x + m_MovementWidth / 2.0f;
				}
			}
		}

	}
}

void SmallSpider::DoIsaacCollisionCheck(Isaac* isaac)
{
	Rectf hitBox{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f, m_MovementWidth, m_MovementHeight };
	if (utils::IsOverlapping(hitBox, isaac->GetHitBox()))
	{
		isaac->TakeDamage(m_Damage);
	}
}

