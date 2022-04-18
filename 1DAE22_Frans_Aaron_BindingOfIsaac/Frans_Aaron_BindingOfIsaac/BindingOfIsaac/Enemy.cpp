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
	Circlef hitbox = GetHitBox();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if ((i != currentEnemyIndex &&
			!enemies[i]->IsDead()))
		{

			Vector2f currentToEnemy{ m_CenterPosition , enemies[i]->m_CenterPosition };
			Vector2f velNorm{ m_Velocity.Normalized() };
			float dot{ velNorm.DotProduct(currentToEnemy) };
			if (dot > 0)
			{
				Circlef enemyHitbox{ enemies[i]->GetHitBox() };
				if (utils::IsOverlapping(hitbox, enemyHitbox) &&
					typeid(*this) == typeid(*enemies[i]))
				{
					float radiusSum{ enemyHitbox.radius + hitbox.radius };
					Vector2f enemyToCurrentNorm{ -(currentToEnemy.Normalized()) };
					Vector2f currentDisplament{ enemyToCurrentNorm * radiusSum };
					m_CenterPosition = enemies[i]->m_CenterPosition + currentDisplament;
				}
			}

		}
	}
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

