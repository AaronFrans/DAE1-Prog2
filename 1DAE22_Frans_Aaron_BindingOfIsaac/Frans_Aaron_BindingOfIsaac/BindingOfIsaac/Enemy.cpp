#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"

Enemy::Enemy(Point2f centerPoint, float damage, float speed)
	: m_CenterPosition{ centerPoint }
	, m_Speed{ speed }
	, m_Velocity{ 0,0 }
	, m_Damage{ damage }
	, m_HasDied{ false }
{
}

