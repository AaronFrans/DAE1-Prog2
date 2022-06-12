#include "pch.h"
#include "Monstro.h"
#include "Texture.h"
#include "utils.h"
#include "Room.h"
#include "Isaac.h"
#include "Tear.h"
#include "TearManager.h"
#include "Sprite.h"
#include "BossHealthBar.h"
#include "SoundEffectManager.h"
#include "SoundEffect.h"

Monstro::Monstro(Texture* spriteSheet, Texture* shadow, Texture* healthBarTexture,
	Texture* deathBloodSheet, Point2f centerPoint, SoundEffectManager* soundEffectManager)
	: Boss{ centerPoint, 1, 100, 25 , healthBarTexture, soundEffectManager }
	, m_pSpriteSheet{ spriteSheet }
	, m_pShadow{ shadow }
	, m_IdleMinTime{ 1.5f }
	, m_IdleAccuTime{ 0 }
	, m_State{ MonstroState::idle }
	, m_SpitChargeAccuTime{ 0 }
	, m_SpitChargeMinTime{ 0.3f }
	, m_SpitAttackAccuTime{ 0 }
	, m_SpitAttackDurTime{ 1 }
	, m_JumpHighSpeed{ 1500 }
	, m_OfScreen{ false }
	, m_JumpAttackHighChargeAccuTime{ 0 }
	, m_JumpAttackHighChargeDurTime{ 0.7f }
	, m_JumpAttackHighFloatAccuTime{ 0 }
	, m_JumpAttackHighFloatMinTime{ 2.5f }
	, m_JumpAttackHighLandAccuTime{ 0 }
	, m_JumpAttackHighLandDurTime{ 0.5f }
	, m_JumpSmallSpeed{ 100 }
	, m_JumpSmallMaxHeight{ 50 }
	, m_JumpAttackLowChargeAccuTime{ 0 }
	, m_JumpAttackLowChargeDurTime{ 0.4f }
	, m_JumpAttackLowLandAccuTime{ 0 }
	, m_JumpAttackLowLandDurTime{ 0.3f }
	, m_SpitNrShots{ 10 }
	, m_HasShotTears{ false }
	, m_MinShotSpeed{ 60 }
	, m_MaxShotSpeed{ 100 }
	, m_MinTearHeight{ 20 }
	, m_MaxTearHeight{ 60 }
	, m_TearRange{ 200 }
	, m_Direction{ Direction::left }
	, m_DyingAccuTime{ 0 }
	, m_PlayedCurrentStateSfx{ false }
	, m_NewDeathSplatterSfxAccuTime{ 0 }
	, m_NewDeathSplatterSfxMinTime{ 0.1f }

{
	m_pDeathBlood = new Sprite{ deathBloodSheet, 4, 4, 1 / 15.f,0,10 };
	m_DyingDurTime = m_pDeathBlood->GetTotalLoopTime() * 4.5f;
	m_SrcWidth = m_pSpriteSheet->GetWidth() / 5.0f;
	m_SrcHeight = m_pSpriteSheet->GetHeight() / 2.0f;
	m_ShapeRadius = m_SrcWidth / 2.0f;
}

Monstro::Monstro(const Monstro& rhs)
	: Boss{ rhs.m_CenterPosition, rhs.m_Damage, rhs.m_Speed, rhs.m_Health, new BossHealthBar(*rhs.m_pHealthBar), rhs.m_pSoundEffectManager }
	, m_pSpriteSheet{ rhs.m_pSpriteSheet }
	, m_pShadow{ rhs.m_pShadow }
	, m_IdleMinTime{ rhs.m_IdleMinTime }
	, m_IdleAccuTime{ rhs.m_IdleAccuTime }
	, m_State{ rhs.m_State }
	, m_SpitChargeAccuTime{ rhs.m_SpitChargeAccuTime }
	, m_SpitChargeMinTime{ rhs.m_SpitChargeMinTime }
	, m_SpitAttackAccuTime{ rhs.m_SpitAttackAccuTime }
	, m_SpitAttackDurTime{ rhs.m_SpitAttackDurTime }
	, m_JumpHighSpeed{ rhs.m_JumpHighSpeed }
	, m_OfScreen{ rhs.m_OfScreen }
	, m_JumpAttackHighChargeAccuTime{ rhs.m_JumpAttackHighChargeAccuTime }
	, m_JumpAttackHighChargeDurTime{ rhs.m_JumpAttackHighChargeDurTime }
	, m_JumpAttackHighFloatAccuTime{ rhs.m_JumpAttackHighFloatAccuTime }
	, m_JumpAttackHighFloatMinTime{ rhs.m_JumpAttackHighFloatMinTime }
	, m_JumpAttackHighLandAccuTime{ rhs.m_JumpAttackHighLandAccuTime }
	, m_JumpAttackHighLandDurTime{ rhs.m_JumpAttackHighLandDurTime }
	, m_JumpSmallSpeed{ rhs.m_JumpSmallSpeed }
	, m_JumpSmallMaxHeight{ rhs.m_JumpSmallMaxHeight }
	, m_JumpAttackLowChargeAccuTime{ rhs.m_JumpAttackLowChargeAccuTime }
	, m_JumpAttackLowChargeDurTime{ rhs.m_JumpAttackLowChargeDurTime }
	, m_JumpAttackLowLandAccuTime{ rhs.m_JumpAttackLowLandAccuTime }
	, m_JumpAttackLowLandDurTime{ rhs.m_JumpAttackLowLandDurTime }
	, m_SpitNrShots{ rhs.m_SpitNrShots }
	, m_HasShotTears{ rhs.m_HasShotTears }
	, m_MinShotSpeed{ rhs.m_MinShotSpeed }
	, m_MaxShotSpeed{ rhs.m_MaxShotSpeed }
	, m_MinTearHeight{ rhs.m_MinTearHeight }
	, m_MaxTearHeight{ rhs.m_MaxTearHeight }
	, m_TearRange{ rhs.m_TearRange }
	, m_Direction{ rhs.m_Direction }
	, m_SrcWidth{ rhs.m_SrcWidth }
	, m_SrcHeight{ rhs.m_SrcHeight }
	, m_ShapeRadius{ rhs.m_ShapeRadius }
	, m_pDeathBlood{ new Sprite{*rhs.m_pDeathBlood} }
	, m_DyingAccuTime{ rhs.m_DyingAccuTime }
	, m_DyingDurTime{ rhs.m_DyingDurTime }
	, m_PlayedCurrentStateSfx{ rhs.m_PlayedCurrentStateSfx }
	, m_NewDeathSplatterSfxAccuTime{ rhs.m_NewDeathSplatterSfxAccuTime }
	, m_NewDeathSplatterSfxMinTime{ rhs.m_NewDeathSplatterSfxMinTime }
{
}

Monstro& Monstro::operator=(const Monstro& rhs)
{
	m_pSoundEffectManager = rhs.m_pSoundEffectManager;
	m_pSpriteSheet = rhs.m_pSpriteSheet;
	m_pShadow = rhs.m_pShadow;
	m_IdleMinTime = rhs.m_IdleMinTime;
	m_IdleAccuTime = rhs.m_IdleAccuTime;
	m_State = rhs.m_State;
	m_SpitChargeAccuTime = rhs.m_SpitChargeAccuTime;
	m_SpitChargeMinTime = rhs.m_SpitChargeMinTime;
	m_SpitAttackAccuTime = rhs.m_SpitAttackAccuTime;
	m_SpitAttackDurTime = rhs.m_SpitAttackDurTime;
	m_JumpHighSpeed = rhs.m_JumpHighSpeed;
	m_OfScreen = rhs.m_OfScreen;
	m_JumpAttackHighChargeAccuTime = rhs.m_JumpAttackHighChargeAccuTime;
	m_JumpAttackHighChargeDurTime = rhs.m_JumpAttackHighChargeDurTime;
	m_JumpAttackHighFloatAccuTime = rhs.m_JumpAttackHighFloatAccuTime;
	m_JumpAttackHighFloatMinTime = rhs.m_JumpAttackHighFloatMinTime;
	m_JumpAttackHighLandAccuTime = rhs.m_JumpAttackHighLandAccuTime;
	m_JumpAttackHighLandDurTime = rhs.m_JumpAttackHighLandDurTime;
	m_JumpSmallSpeed = rhs.m_JumpSmallSpeed;
	m_JumpSmallMaxHeight = rhs.m_JumpSmallMaxHeight;
	m_JumpAttackLowChargeAccuTime = rhs.m_JumpAttackLowChargeAccuTime;
	m_JumpAttackLowChargeDurTime = rhs.m_JumpAttackLowChargeDurTime;
	m_JumpAttackLowLandAccuTime = rhs.m_JumpAttackLowLandAccuTime;
	m_JumpAttackLowLandDurTime = rhs.m_JumpAttackLowLandDurTime;
	m_SpitNrShots = rhs.m_SpitNrShots;
	m_HasShotTears = rhs.m_HasShotTears;
	m_MinShotSpeed = rhs.m_MinShotSpeed;
	m_MaxShotSpeed = rhs.m_MaxShotSpeed;
	m_MinTearHeight = rhs.m_MinTearHeight;
	m_MaxTearHeight = rhs.m_MaxTearHeight;
	m_TearRange = rhs.m_TearRange;
	m_Direction = rhs.m_Direction;
	m_SrcWidth = rhs.m_SrcWidth;
	m_SrcHeight = rhs.m_SrcHeight;
	m_ShapeRadius = rhs.m_ShapeRadius;
	m_pDeathBlood = new Sprite{ *rhs.m_pDeathBlood };
	m_DyingDurTime = rhs.m_DyingDurTime;
	m_DyingAccuTime = rhs.m_DyingAccuTime;
	m_pHealthBar = rhs.m_pHealthBar;
	m_PlayedCurrentStateSfx = rhs.m_PlayedCurrentStateSfx;
	m_NewDeathSplatterSfxAccuTime = rhs.m_NewDeathSplatterSfxAccuTime;
	m_NewDeathSplatterSfxMinTime = rhs.m_NewDeathSplatterSfxMinTime;


	return *this;
}

Monstro::~Monstro()
{
	delete m_pDeathBlood;
	m_pDeathBlood = nullptr;
}


void Monstro::Draw() const
{
	Rectf shadow{ m_CenterPosition.x - m_ShapeRadius, m_CenterPosition.y - m_ShapeRadius / 2.0f , m_ShapeRadius * 2, m_ShapeRadius };
	m_pShadow->Draw(shadow);
	if (!m_OfScreen)
	{
		Rectf srcRect{};
		switch (m_State)
		{
		case Monstro::MonstroState::idle:

			switch (m_Direction)
			{
			case Monstro::Direction::left:

				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 1,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 1,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);
				glPopMatrix();

				break;
			}

			break;
		case Monstro::MonstroState::charginSpit:

			srcRect = Rectf{ m_SrcWidth * 1, m_SrcHeight * 1,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);

			break;
		case Monstro::MonstroState::attackSpit:

			switch (m_Direction)
			{

			case Monstro::Direction::left:
				srcRect = Rectf{ m_SrcWidth * 3, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 3, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);
				glPopMatrix();

				break;
			}

			break;
		case Monstro::MonstroState::jumpHighStart:

			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);

			break;
		case Monstro::MonstroState::jumpHighUp:

			srcRect = Rectf{ m_SrcWidth * 4, m_SrcHeight * 1,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);

			break;
		case Monstro::MonstroState::jumpHighDown:

			srcRect = Rectf{ m_SrcWidth * 4, m_SrcHeight * 1,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);

			break;
		case Monstro::MonstroState::jumpHighEnd:

			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);

			break;
		case Monstro::MonstroState::jumpSmallStart:

			switch (m_Direction)
			{
			case Monstro::Direction::left:
				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);
				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);
				glPopMatrix();
				break;
			}

			break;
		case Monstro::MonstroState::jumpSmallUp:

			switch (m_Direction)
			{
			case Monstro::Direction::left:

				srcRect = Rectf{ m_SrcWidth * 1, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 1, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				glPopMatrix();

				break;
			}

			break;
		case Monstro::MonstroState::jumpSmallDown:
			switch (m_Direction)
			{
			case Monstro::Direction::left:

				srcRect = Rectf{ m_SrcWidth * 2, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 2, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				glPopMatrix();

				break;
			}

			break;
		case Monstro::MonstroState::jumpSmallEnd:
			switch (m_Direction)
			{
			case Monstro::Direction::left:

				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				break;
			case Monstro::Direction::right:

				glPushMatrix();
				glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
				glScalef(-1, 1, 1);
				glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

				srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
				m_pSpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
					m_CenterPosition.y + m_Height },
					srcRect);

				glPopMatrix();

				break;

			}
			break;
		case Monstro::MonstroState::dying:
			Point2f drawBottomLeft{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height };
			m_pDeathBlood->Draw(Point2f{ drawBottomLeft.x, drawBottomLeft.y });
			m_pDeathBlood->Draw(Point2f{ drawBottomLeft.x, drawBottomLeft.y + m_SrcHeight / 6.0f });
			srcRect = Rectf{ m_SrcWidth * 3, m_SrcHeight * 0,m_SrcWidth, m_SrcHeight };
			m_pSpriteSheet->Draw(drawBottomLeft, srcRect);
			m_pDeathBlood->Draw(Point2f{ drawBottomLeft.x + m_SrcWidth / 2.0f, drawBottomLeft.y });
			m_pDeathBlood->Draw(Point2f{ drawBottomLeft.x + m_SrcWidth / 2.0f, drawBottomLeft.y - m_SrcHeight / 6.0f });
			break;
		}

	}
}

void Monstro::Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
	const Room* currentRoom, Isaac* isaac, int currentEnemyIndex)
{

	switch (m_State)
	{
	case Monstro::MonstroState::idle:
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::charginSpit:
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::attackSpit:
		if (!m_PlayedCurrentStateSfx)
		{
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::spit1,
				(int)SoundEffectManager::SoundEffectLookup::spit3) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(15);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}

		if (!m_HasShotTears)
		{

			UpdateDirection(isaac);
		}
		ShootBullets(isaac, tearManager, textureManager);
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpHighStart:
		if (!m_PlayedCurrentStateSfx)
		{
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::jumpRoar1,
				(int)SoundEffectManager::SoundEffectLookup::jumpRoar4) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(15);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}

		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpHighUp:
	{
		Rectf roomBounds{ currentRoom->GetBoundaries() };
		if (!m_OfScreen)
		{
			if (roomBounds.bottom + roomBounds.height >= m_CenterPosition.y + m_Height)
			{
				m_Height += m_JumpHighSpeed * elapsedSec;
			}
			else
			{
				m_OfScreen = true;
			}
		}
		else
		{
			UpdatePos(elapsedSec, isaac);
		}

		break;
	}
	case Monstro::MonstroState::jumpHighDown:
		m_OfScreen = false;
		if (m_Height > 0)
		{
			m_Height -= m_JumpHighSpeed * elapsedSec;
			if (m_Height <= 0)
			{
				//Tears around Monstro
				m_Height = 0;
			}
		}
		break;
	case Monstro::MonstroState::jumpHighEnd:
		if (!m_PlayedCurrentStateSfx)
		{
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::jumpAttack1,
				(int)SoundEffectManager::SoundEffectLookup::jumpAttack3) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(15);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}
		ShootBullets(isaac, tearManager, textureManager);
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpSmallStart:
		if (!m_PlayedCurrentStateSfx)
		{
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::jumpRoar1,
				(int)SoundEffectManager::SoundEffectLookup::jumpRoar4) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(15);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}
		UpdateDirection(isaac);
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpSmallUp:
		if (m_JumpSmallMaxHeight >= m_Height)
		{
			m_Height += m_JumpSmallSpeed * elapsedSec;
			UpdatePos(elapsedSec, isaac);
		}
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpSmallDown:
		if (m_Height >= 0)
		{
			m_Height -= m_JumpSmallSpeed * elapsedSec;
			UpdatePos(elapsedSec, isaac);
			if (m_Height <= 0)
			{
				m_Height = 0;
			}
		}
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::jumpSmallEnd:
		if (!m_PlayedCurrentStateSfx)
		{
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::jumpAttack1,
				(int)SoundEffectManager::SoundEffectLookup::jumpAttack3) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(15);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}
		DoIsaacCollisionCheck(isaac);
		break;
	case Monstro::MonstroState::dying:

		m_NewDeathSplatterSfxAccuTime += elapsedSec;
		if (m_NewDeathSplatterSfxMinTime <= m_NewDeathSplatterSfxAccuTime)
		{
			m_NewDeathSplatterSfxAccuTime = 0;
			int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::deathSplatter1,
				(int)SoundEffectManager::SoundEffectLookup::deathSplatter3) };

			SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
			effect->SetVolume(10);
			effect->Play(0);
			m_PlayedCurrentStateSfx = true;
		}



		m_pDeathBlood->Update(elapsedSec);
		m_DyingAccuTime += elapsedSec;
		break;
	}
	ChangeState(elapsedSec);

}

void Monstro::TakeDamage(float damage)
{
	m_Health -= damage;
	m_pHealthBar->TakeDamage(damage);
	if (m_Health <= 0)
	{
		m_Health = 0;
		m_Height = 0;
		m_State = MonstroState::dying;
	}

}

bool Monstro::IsDead() const
{
	return m_State == MonstroState::dying || m_State == MonstroState::dead;;
}

Circlef Monstro::GetHitBox() const
{
	Point2f hitboxCenter{ m_CenterPosition.x, m_CenterPosition.y + m_ShapeRadius / 2.0f + m_Height };
	return Circlef{ hitboxCenter, m_ShapeRadius / 1.5f };
}

Enemy* Monstro::Clone() const
{
	return new Monstro{ *this };
}

void Monstro::ChangeState(float elapsedSec)
{

	switch (m_State)
	{
	case Monstro::MonstroState::idle:
		m_IdleAccuTime += elapsedSec;
		if (m_IdleAccuTime >= m_IdleMinTime)
		{
			int nextAttack{ utils::GetRand(0,5) };
			if (nextAttack == 1)
			{
				m_PlayedCurrentStateSfx = false;
				m_State = MonstroState::charginSpit;
				m_IdleAccuTime = 0;
			}
			else if (nextAttack == (2))
			{
				m_PlayedCurrentStateSfx = false;
				m_State = MonstroState::jumpHighStart;
				m_IdleAccuTime = 0;
			}
			else if (nextAttack >= 3)
			{
				m_PlayedCurrentStateSfx = false;
				m_State = MonstroState::jumpSmallStart;
				m_IdleAccuTime = 0;
			}
		}
		break;
	case Monstro::MonstroState::charginSpit:
		m_SpitChargeAccuTime += elapsedSec;
		if (m_SpitChargeAccuTime >= m_SpitChargeMinTime)
		{
			int spitAttack{ utils::GetRand(0,3) };
			if (spitAttack == 3)
			{
				m_PlayedCurrentStateSfx = false;
				m_State = MonstroState::attackSpit;
				m_SpitChargeAccuTime = 0;
			}
		}
		break;
	case Monstro::MonstroState::attackSpit:
		m_SpitAttackAccuTime += elapsedSec;
		if (m_SpitAttackAccuTime >= m_SpitAttackDurTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::idle;
			m_SpitAttackAccuTime = 0;
			m_HasShotTears = false;
		}
		break;
	case Monstro::MonstroState::jumpHighStart:
		m_JumpAttackHighChargeAccuTime += elapsedSec;
		if (m_JumpAttackHighChargeAccuTime >= m_JumpAttackHighChargeDurTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::jumpHighUp;
			m_JumpAttackHighChargeAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::jumpHighUp:
		if (m_OfScreen)
		{
			m_JumpAttackHighFloatAccuTime += elapsedSec;
			if (m_JumpAttackHighFloatAccuTime >= m_JumpAttackHighFloatMinTime)
			{
				int land{ utils::GetRand(0, 3) };
				if (land == 3)
				{
					m_PlayedCurrentStateSfx = false;
					m_State = MonstroState::jumpHighDown;
					m_JumpAttackHighFloatAccuTime = 0;
				}
			}
		}
		break;
	case Monstro::MonstroState::jumpHighDown:
		if (m_Height == 0)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::jumpHighEnd;
		}
		break;
	case Monstro::MonstroState::jumpHighEnd:
		m_JumpAttackHighLandAccuTime += elapsedSec;
		if (m_JumpAttackHighLandAccuTime >= m_JumpAttackHighLandDurTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::idle;
			m_JumpAttackHighLandAccuTime = 0;
			m_HasShotTears = false;
		}
		break;
	case Monstro::MonstroState::jumpSmallStart:
		m_JumpAttackLowChargeAccuTime += elapsedSec;
		if (m_JumpAttackLowChargeAccuTime >= m_JumpAttackLowChargeDurTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::jumpSmallUp;
			m_JumpAttackLowChargeAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::jumpSmallUp:
		if (m_JumpSmallMaxHeight <= m_Height)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::jumpSmallDown;
		}
		break;
	case Monstro::MonstroState::jumpSmallDown:
		if (m_Height == 0)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::jumpSmallEnd;
		}
		break;
	case Monstro::MonstroState::jumpSmallEnd:
		m_JumpAttackLowLandAccuTime += elapsedSec;
		if (m_JumpAttackLowLandAccuTime >= m_JumpAttackLowLandDurTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::idle;
			m_JumpAttackLowLandAccuTime = 0;
			m_SmallJumpTarget = Point2f{};
		}
		break;
	case Monstro::MonstroState::dying:
		if (m_DyingDurTime <= m_DyingAccuTime)
		{
			m_PlayedCurrentStateSfx = false;
			m_State = MonstroState::dead;
			m_DeathState = Boss::DeathState::death;
		}

		break;
	}

}

void Monstro::UpdatePos(float elapsedSec, Isaac* isaac)
{
	switch (m_State)
	{
	case Monstro::MonstroState::jumpHighUp:
	{

		Vector2f direction{ m_CenterPosition, isaac->GetCenter() };
		direction = direction.Normalized();
		direction *= m_Speed;
		m_CenterPosition += direction * elapsedSec;
		break;
	}
	case Monstro::MonstroState::jumpSmallUp:
	case Monstro::MonstroState::jumpSmallDown:
	{
		if (m_SmallJumpTarget.x == 0 && m_SmallJumpTarget.y == 0)
		{
			m_SmallJumpTarget = isaac->GetCenter();
		}
		Vector2f direction{ m_CenterPosition, m_SmallJumpTarget };
		direction = direction.Normalized();
		direction *= m_Speed;
		m_CenterPosition += direction * elapsedSec;
		break;
	}
	}
}

void Monstro::DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex)
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
			}
		}

	}
}

void Monstro::ShootBullets(Isaac* isaac, TearManager* tearManager, const TextureManager& textureManager)
{

	switch (m_State)
	{
	case Monstro::MonstroState::attackSpit:
		if (!m_HasShotTears)
		{
			m_SpitNrShots = 15;
			Vector2f direction{ m_CenterPosition, isaac->GetCenter() };
			direction = direction.Normalized();
			float  directionAngle = atan2f(direction.y, direction.x);
			float minAngle{ directionAngle - 0.523f }, maxAngle{ directionAngle + 0.523f };

			Vector2f shotDirection;
			float shotAngle, shotSpeed;
			for (size_t i = 0; i < m_SpitNrShots; i++)
			{
				shotAngle = utils::GetRand(minAngle, maxAngle, 2);
				shotSpeed = utils::GetRand(m_MinShotSpeed, m_MaxShotSpeed, 0);
				shotDirection = Vector2f{ shotSpeed * cosf(shotAngle), shotSpeed * sinf(shotAngle) };
				Shoot(tearManager, textureManager, shotDirection);
			}
			m_HasShotTears = true;
		}

		break;
	case Monstro::MonstroState::jumpHighEnd:

		if (!m_HasShotTears)
		{
			m_SpitNrShots = 20;
			Vector2f shotDirection;

			for (size_t i = 0; i < m_SpitNrShots; i++)
			{

				float xSpeed{ utils::GetRand(m_MinShotSpeed, m_MaxShotSpeed, 1) };
				int xSign{ utils::GetRand(0,1) };
				if (xSign == 0)
					xSpeed = -xSpeed;


				float ySpeed{ utils::GetRand(m_MinShotSpeed, m_MaxShotSpeed, 1) };
				int ySign{ utils::GetRand(0,1) };
				if (ySign == 0)
					ySpeed = -ySpeed;

				Vector2f shotDirection = Vector2f{ xSpeed, ySpeed };
				Shoot(tearManager, textureManager, shotDirection);
			}
			m_HasShotTears = true;
		}

		break;
	}


}

void Monstro::Shoot(TearManager* tearManager, const TextureManager& textureManager, Vector2f tearVelocity)
{
	Tear* pShotTear = tearManager->ShootTear();
	Point2f tearCenterPos = m_CenterPosition;

	pShotTear->SetTearTexture(textureManager.GetTexture(TextureManager::TextureLookup::enemyTear));
	pShotTear->SetTearHitSprite(textureManager.GetTexture(TextureManager::TextureLookup::isaacTearHit));
	float tearSize{ utils::GetRand(3.0f,7.0f, 0) };
	pShotTear->SetTearShape(tearCenterPos, tearSize);
	pShotTear->SetVelocity(tearVelocity + (m_Velocity / 4.0));
	pShotTear->SetHeight((float)utils::GetRand(m_MinTearHeight, m_MaxTearHeight));
	pShotTear->SetRange(m_TearRange);
	pShotTear->SetIsFront(false);
	pShotTear->SetDamage(m_Damage);
	pShotTear->SetShooter(Tear::Shooter::enemy);


	int soundEffect{ utils::GetRand((int)SoundEffectManager::SoundEffectLookup::splatter1,
				(int)SoundEffectManager::SoundEffectLookup::splatter3) };

	SoundEffect* effect{ m_pSoundEffectManager->GetSoundEffect((SoundEffectManager::SoundEffectLookup)soundEffect) };
	pShotTear->SetLandSoundEffect(effect);



}

void Monstro::DoIsaacCollisionCheck(Isaac* isaac)
{
	if (utils::IsOverlapping(isaac->GetHitBox(), GetHitBox()))
	{
		isaac->TakeDamage(m_Damage);
	}
}

void Monstro::UpdateDirection(Isaac* isaac)
{
	Vector2f direction{ m_CenterPosition, isaac->GetCenter() };
	if (direction.x <= 0)
		m_Direction = Direction::left;
	else
		m_Direction = Direction::right;
}
