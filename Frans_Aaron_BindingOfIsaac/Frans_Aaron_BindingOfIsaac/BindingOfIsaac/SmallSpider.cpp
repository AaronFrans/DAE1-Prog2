#include "pch.h"
#include "SmallSpider.h"
#include "Sprite.h"
#include "Room.h"
#include "GameObject.h"
#include "utils.h"
#include "Isaac.h"
#include "TearManager.h"
#include "Texture.h"
#include "SoundEffectManager.h"
#include "SoundEffect.h"

SmallSpider::SmallSpider(Texture* movementSpriteSheet, Texture* DyingSpriteSheet, Point2f centerPoint, SoundEffectManager* soundEffectManger)
	: Enemy{ centerPoint, 0.5f, 150, 6.5, soundEffectManger }
	, m_State{ SmallSpiderState::idle }
	, m_MovementAccuSec{ 0 }
	, m_IdleAccuSec{ 0 }
	, m_IdleMinSec{ 0.5 }
	, m_DyingAccuSec{ 0 }
{
	m_pMovementSprite = new Sprite(movementSpriteSheet, 2, 2, 1 / 15.0f, 1);
	m_MovementWidth = m_pMovementSprite->GetFrameWidth();
	m_MovementHeight = m_pMovementSprite->GetFrameHeight();


	m_MovementMaxSec = m_pMovementSprite->GetTotalLoopTime();

	m_pDyingSprite = new Sprite(DyingSpriteSheet, 4, 3, 1 / 15.0f, 1, 11);
	m_DyingWidth = m_pDyingSprite->GetFrameWidth();
	m_DyingHeight = m_pDyingSprite->GetFrameHeight();
	m_DyingMaxSec = m_pDyingSprite->GetTotalLoopTime();

	m_Height = 5;
}

SmallSpider::SmallSpider(const SmallSpider& rhs)
	: Enemy{ rhs.m_CenterPosition , 0.5f, 150,  6.5, rhs.m_pSoundEffectManager }
	, m_State{ rhs.m_State }
	, m_MovementAccuSec{ 0 }
	, m_IdleAccuSec{ 0 }
	, m_IdleMinSec{ 0.5 }
	, m_DyingAccuSec{ 0 }
{
	m_pMovementSprite = new Sprite{ *rhs.m_pMovementSprite };
	m_MovementWidth = rhs.m_MovementWidth;
	m_MovementHeight = rhs.m_MovementHeight;


	m_MovementMaxSec = rhs.m_MovementMaxSec;

	m_pDyingSprite = new Sprite{ *rhs.m_pDyingSprite };
	m_DyingWidth = rhs.m_DyingWidth;
	m_DyingHeight = rhs.m_DyingHeight;
	m_DyingMaxSec = rhs.m_DyingMaxSec;

	m_Height = rhs.m_Height;
}

SmallSpider& SmallSpider::operator=(const SmallSpider& rhs)
{
	m_CenterPosition = rhs.m_CenterPosition;
	m_Damage = rhs.m_Damage;
	m_Speed = rhs.m_Speed;
	m_Health = rhs.m_Health;
	m_pMovementSprite = new Sprite{ *rhs.m_pMovementSprite };
	m_pSoundEffectManager = rhs.m_pSoundEffectManager;

	m_State = rhs.m_State;
	m_MovementAccuSec = 0;
	m_IdleAccuSec = 0;
	m_IdleMinSec = rhs.m_IdleMinSec;
	m_DyingAccuSec = 0;
	m_MovementWidth = rhs.m_MovementWidth;
	m_MovementHeight = rhs.m_MovementHeight;


	m_MovementMaxSec = rhs.m_MovementMaxSec;

	m_pDyingSprite = new Sprite{ *rhs.m_pDyingSprite };
	m_DyingWidth = rhs.m_DyingWidth;
	m_DyingHeight = rhs.m_DyingHeight;
	m_DyingMaxSec = rhs.m_DyingMaxSec;

	m_Height = rhs.m_Height;
	return *this;
}

SmallSpider::~SmallSpider()
{
	delete m_pMovementSprite;
	m_pMovementSprite = nullptr;
	delete m_pDyingSprite;
	m_pDyingSprite = nullptr;

}

void SmallSpider::Draw() const
{
	switch (m_State)
	{
	case SmallSpiderState::idle:
	{

		m_pMovementSprite->Draw(Rectf{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f,
			m_MovementWidth, m_MovementHeight });
		break;
	}
	case SmallSpiderState::moving:
	{

		m_pMovementSprite->Draw(Rectf{ m_CenterPosition.x - m_MovementWidth / 2.0f,m_CenterPosition.y - m_MovementHeight / 2.0f,
			m_MovementWidth, m_MovementHeight });
		break;
	}
	case SmallSpiderState::dying:
		m_pDyingSprite->Draw(Rectf{ m_CenterPosition.x - m_DyingWidth / 2.0f,m_CenterPosition.y - m_DyingHeight / 2.0f,
			m_DyingWidth, m_DyingHeight });
		break;
	default:
		break;
	}

}

void SmallSpider::Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
	const Room* currentRoom, Isaac* isaac, int currentEnemyIndex)
{
	switch (m_State)
	{
	case SmallSpiderState::idle:
		m_pMovementSprite->SetAccuSec(0);
		m_pMovementSprite->SetActFrame(0);
		m_Velocity = Vector2f{ 0, 0 };
		DoIdle(elapsedSec);
		DoIsaacCollisionCheck(isaac);
		break;
	case SmallSpiderState::moving:
		m_pMovementSprite->Update(elapsedSec);
		if (m_Velocity == Vector2f{ 0,0 })
		{
			m_Velocity.x += utils::GetRand(-m_Speed, m_Speed, 2);
			m_Velocity.y += utils::GetRand(-m_Speed, m_Speed, 2);
		}
		UpdatePos(elapsedSec, currentRoom);
		DoIsaacCollisionCheck(isaac);
		DoEnemyCollisions(currentRoom->GetEnemies(), currentEnemyIndex);
		break;
	case SmallSpiderState::dying:
		if (!m_PlayedDeathSound)
		{

			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::animalDeathSound1,
				(int)SoundEffectManager::SoundEffectLookup::animalDeathSound3) };
			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(25);
			effect->Play(0);
			m_PlayedDeathSound = true;
		}
		DoDying(elapsedSec);
		break;
	default:
		break;
	}
}

bool SmallSpider::IsDead() const
{
	return m_State == SmallSpiderState::dying || m_State == SmallSpiderState::dead;
}

Circlef SmallSpider::GetHitBox() const
{
	return Circlef{ m_CenterPosition, m_MovementHeight / 2.0f };
}

void SmallSpider::TakeDamage(float damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_State = SmallSpiderState::dying;
	}
}

Enemy* SmallSpider::Clone() const
{
	return new SmallSpider{ *this };
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

void SmallSpider::DoGameObjectCollision(const std::vector<GameObject*>& objects)
{
	Circlef hitbox{ GetHitBox() };

	for (GameObject* object : objects)
	{
		if (object->IsNotDestroyed())
		{
			Vector2f currentToEnemy{ m_CenterPosition , object->GetCenter() };
			Circlef objectShape{ object->GetShape() };
			if (utils::IsOverlapping(hitbox, objectShape))
			{
				float radiusSum{ objectShape.radius + hitbox.radius };
				Vector2f enemyToCurrentNorm{ -(currentToEnemy.Normalized()) };
				Vector2f currentDisplament{ enemyToCurrentNorm * radiusSum };
				m_CenterPosition = object->GetCenter() + currentDisplament;
			}
		}

	}
}

void SmallSpider::DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex)
{
	Circlef hitbox = GetHitBox();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if ((i != currentEnemyIndex &&
			!enemies[i]->IsDead()))
		{
			Point2f otherCenter{ enemies[i]->GetCenter() };
			Vector2f currentToEnemy{ m_CenterPosition ,otherCenter };
			Circlef enemyHitbox{ enemies[i]->GetHitBox() };
			if (utils::IsOverlapping(hitbox, enemyHitbox))
			{
				float radiusSum{ enemyHitbox.radius + hitbox.radius };
				Vector2f enemyToCurrentNorm{ -(currentToEnemy.Normalized()) };
				Vector2f currentDisplament{ enemyToCurrentNorm * radiusSum };
				m_CenterPosition = otherCenter + currentDisplament;
				m_Velocity = -m_Velocity;
			}
		}

	}
}

void SmallSpider::DoIsaacCollisionCheck(Isaac* isaac)
{
	if (utils::IsOverlapping(isaac->GetHitBox(), GetHitBox()))
	{
		isaac->TakeDamage(m_Damage);
	}
}

void SmallSpider::DoDying(float elapsedSec)
{
	m_DyingAccuSec += elapsedSec;
	if (m_DyingAccuSec >= m_DyingMaxSec)
		m_State = SmallSpiderState::dead;
	else
		m_pDyingSprite->Update(elapsedSec);
}

