#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"
#include "utils.h"
#include "Room.h"

Enemy::Enemy(Point2f centerPoint, float damage, float speed, float health)
	: m_CenterPosition{ centerPoint }
	, m_Speed{ speed }
	, m_Velocity{ 0,0 }
	, m_Damage{ damage }
	, m_HasDied{ false }
	, m_Health{ health }
{
}

void Enemy::SetPosition(const Point2f& center)
{
	m_CenterPosition = center;
}

void Enemy::DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex)
{
	utils::HitInfo hitInfo;
	Rectf hitbox = GetHitBox();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		Rectf enemyHitbox{ enemies[i]->GetHitBox() };
		if (i != currentEnemyIndex &&
			!enemies[i]->IsDead() &&
			utils::IsOverlapping(hitbox, enemyHitbox)&&
			typeid(*this) == typeid(*enemies[i]))
		{
			float minX{ hitbox.left + hitbox.width > enemyHitbox.left + enemyHitbox.width ?
				enemyHitbox.left + enemyHitbox.width : hitbox.left + hitbox.width };
			float minY{ hitbox.bottom + hitbox.height > enemyHitbox.bottom + enemyHitbox.height ?
				enemyHitbox.bottom + enemyHitbox.height : hitbox.bottom + hitbox.height };

			float maxX{ hitbox.left < enemyHitbox.left ?
				enemyHitbox.left : hitbox.left };
			float maxY{ hitbox.bottom < enemyHitbox.bottom ?
				enemyHitbox.bottom : hitbox.bottom };

			float distHoriz = minX - maxX;
			float distVert = minY - maxY;

			if (abs(distHoriz) < abs(distVert))
			{
				if (m_Velocity.y > 0)
				{
					m_CenterPosition.x += distHoriz + 1.0f;
				}
				else
				{
					m_CenterPosition.x -= distHoriz - 1.0f;
				}
			}
			{
				if (m_Velocity.x > 0)
				{
					m_CenterPosition.y += distVert + 1.0f;
				}
				else
				{
					m_CenterPosition.y -= distVert - 1.0f;
				}
			}
		}
	}
}


void Enemy::DoRoomCollision(const Room* currentRoom)
{
	utils::HitInfo hitInfo;
	Rectf hitbox = GetHitBox();
	std::vector<Point2f> hitboxPoints{ utils::GetVertices(hitbox) };
	Point2f bottomLeft{ hitboxPoints[0] };
	Point2f bottomRight{ hitboxPoints[1] };
	Point2f topRight{ hitboxPoints[2] };
	Point2f topLeft{ hitboxPoints[3] };
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), topRight, bottomRight, hitInfo) ||
		utils::Raycast(currentRoom->GetWalkableAreaVertices(), topLeft, bottomLeft, hitInfo))
	{
		if (m_Velocity.y > 0)
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y - hitbox.height / 2.0f;
			m_Velocity.y = -m_Velocity.y;
		}
		else
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y + hitbox.height / 2.0f;
			m_Velocity.y = -m_Velocity.y;
		}
	}
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), topLeft, topRight, hitInfo) ||
		utils::Raycast(currentRoom->GetWalkableAreaVertices(), bottomRight, bottomLeft, hitInfo))
	{
		if (m_Velocity.x > 0)
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x - hitbox.width / 2.0f;
			m_Velocity.x = -m_Velocity.x;
		}
		else
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x + hitbox.width / 2.0f;
			m_Velocity.x = -m_Velocity.x;
		}
	}
}

