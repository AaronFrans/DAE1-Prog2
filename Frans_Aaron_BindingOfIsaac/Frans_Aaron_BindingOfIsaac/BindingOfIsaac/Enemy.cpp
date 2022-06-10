#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"
#include "utils.h"
#include "Room.h"
#include <typeinfo>

Enemy::Enemy(Point2f centerPoint, float damage, float speed, float health, SoundEffectManager* soundEffectManager)
	: m_CenterPosition{ centerPoint }
	, m_Speed{ speed }
	, m_Velocity{ 0,0 }
	, m_Damage{ damage }
	, m_HasDied{ false }
	, m_Health{ health }
	, m_Height{ 0 }
	, m_pSoundEffectManager{ soundEffectManager }
	, m_PlayedDeathSound{ false }
{
}

void Enemy::SetPosition(const Point2f& center)
{
	m_CenterPosition = center;
}

Point2f Enemy::GetCenter()
{
	return m_CenterPosition;
}




void Enemy::DoRoomCollision(const Room* currentRoom)
{
	utils::HitInfo hitInfo;
	Circlef hitbox = GetHitBox();
	Point2f bottom{ hitbox.center.x, hitbox.center.y - hitbox.radius };
	Point2f top{ hitbox.center.x, hitbox.center.y + hitbox.radius };
	Point2f left{ hitbox.center.x - hitbox.radius,  hitbox.center.y };
	Point2f right{ hitbox.center.x + hitbox.radius,  hitbox.center.y };

	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), bottom, top, hitInfo))
	{
		if (m_Velocity.y > 0)
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y - hitbox.radius;
			m_Velocity.y = -m_Velocity.y;
		}
		else
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y + hitbox.radius;
			m_Velocity.y = -m_Velocity.y;
		}
	}
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), left, right, hitInfo))
	{
		if (m_Velocity.x > 0)
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x - hitbox.radius;
			m_Velocity.x = -m_Velocity.x;
		}
		else
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x + hitbox.radius;
			m_Velocity.x = -m_Velocity.x;
		}
	}
}

