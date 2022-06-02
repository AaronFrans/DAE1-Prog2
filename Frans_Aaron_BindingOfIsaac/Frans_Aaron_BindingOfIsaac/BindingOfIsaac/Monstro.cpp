#include "pch.h"
#include "Monstro.h"
#include "Texture.h"
#include "utils.h"
#include "room.h"

Monstro::Monstro(Texture* spriteSheet, Point2f centerPoint, float damage, float speed, float health)
	: Boss{ centerPoint, damage,  speed,  health }
	, m_SpriteSheet{ spriteSheet }
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
	, m_Height{ 0 }
	, m_JumpSmallSpeed{ 100 }
	, m_JumpSmallMaxHeight{ 50 }
	, m_JumpAttackLowChargeAccuTime{ 0 }
	, m_JumpAttackLowChargeDurTime{ 0.4f }
	, m_JumpAttackLowLandAccuTime{ 0 }
	, m_JumpAttackLowLandDurTime{ 0.3f }

{
	m_SrcWidth = m_SpriteSheet->GetWidth() / 5.0f;
	m_SrcHeight = m_SpriteSheet->GetHeight() / 2.0f;
}


void Monstro::Draw() const
{
	if (!m_OfScreen)
	{
		Rectf srcRect{};
		switch (m_State)
		{
		case Monstro::MonstroState::idle:
			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::charginSpit:
			srcRect = Rectf{ m_SrcWidth * 1, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::attackSpit:
			srcRect = Rectf{ m_SrcWidth * 3, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpHighStart:
			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpHighUp:
			srcRect = Rectf{ m_SrcWidth * 4, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpHighDown:
			srcRect = Rectf{ m_SrcWidth * 4, m_SrcHeight * 1,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpHighEnd:
			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpSmallStart:
			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpSmallUp:
			srcRect = Rectf{ m_SrcWidth * 1, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpSmallDown:
			srcRect = Rectf{ m_SrcWidth * 2, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::jumpSmallEnd:
			srcRect = Rectf{ m_SrcWidth * 0, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::dying:
			srcRect = Rectf{ m_SrcWidth * 3, m_SrcHeight * 0,m_SrcWidth, m_SrcWidth };
			m_SpriteSheet->Draw(Point2f{ m_CenterPosition.x - m_SrcWidth / 2.0f,
				m_CenterPosition.y + m_Height },
				srcRect);
			break;
		case Monstro::MonstroState::dead:
			break;
		default:
			break;
		}

	}
}

void Monstro::Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex)
{

	switch (m_State)
	{
	case Monstro::MonstroState::attackSpit:
		//Spit Tears
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
			//gotoplayerpos
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
	case Monstro::MonstroState::jumpSmallUp:
		if (m_JumpSmallMaxHeight >= m_Height)
		{
			m_Height += m_JumpSmallSpeed * elapsedSec;
		}
		break;
	case Monstro::MonstroState::jumpSmallDown:
		if (m_Height >= 0)
		{
			m_Height -= m_JumpSmallSpeed * elapsedSec;
			if (m_Height <= 0)
			{
				m_Height = 0;
			}
		}
		break;
	case Monstro::MonstroState::dying:
		break;
	}
	ChangeState(elapsedSec);
}

void Monstro::TakeDamage(float damage)
{

}

bool Monstro::IsDead() const
{
	return false;
}

Circlef Monstro::GetHitBox() const
{
	return Circlef();
}

Enemy* Monstro::Clone() const
{
	return nullptr;
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
			/*if (nextAttack == 1)
			{
				m_State = MonstroState::charginSpit;
				m_IdleAccuTime = 0;
			}
			else if (nextAttack == (2))
			{
				m_State = MonstroState::jumpHighStart;
				m_IdleAccuTime = 0;
			}
			else*/ if (nextAttack >= 3)
			{
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
				m_State = MonstroState::attackSpit;
				m_SpitChargeAccuTime = 0;
			}
		}
		break;
	case Monstro::MonstroState::attackSpit:
		m_SpitAttackAccuTime += elapsedSec;
		if (m_SpitAttackAccuTime >= m_SpitAttackDurTime)
		{
			m_State = MonstroState::idle;
			m_SpitAttackAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::jumpHighStart:
		m_JumpAttackHighChargeAccuTime += elapsedSec;
		if (m_JumpAttackHighChargeAccuTime >= m_JumpAttackHighChargeDurTime)
		{
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
					m_State = MonstroState::jumpHighDown;
					m_JumpAttackHighFloatAccuTime = 0;
				}
			}
		}
		break;
	case Monstro::MonstroState::jumpHighDown:
		if (m_Height == 0)
		{
			m_State = MonstroState::jumpHighEnd;
		}
		break;
	case Monstro::MonstroState::jumpHighEnd:
		m_JumpAttackHighLandAccuTime += elapsedSec;
		if (m_JumpAttackHighLandAccuTime >= m_JumpAttackHighLandDurTime)
		{
			m_State = MonstroState::idle;
			m_JumpAttackHighLandAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::jumpSmallStart:
		m_JumpAttackLowChargeAccuTime += elapsedSec;
		if (m_JumpAttackLowChargeAccuTime >= m_JumpAttackLowChargeDurTime)
		{
			m_State = MonstroState::jumpSmallUp;
			m_JumpAttackLowChargeAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::jumpSmallUp:
		if (m_JumpSmallMaxHeight <= m_Height)
		{
			m_State = MonstroState::jumpSmallDown;
		}
		break;
	case Monstro::MonstroState::jumpSmallDown:
		if (m_Height == 0)
		{
			m_State = MonstroState::jumpSmallEnd;
		}
		break;
	case Monstro::MonstroState::jumpSmallEnd:
		m_JumpAttackLowLandAccuTime += elapsedSec;
		if (m_JumpAttackLowLandAccuTime >= m_JumpAttackLowLandDurTime)
		{
			m_State = MonstroState::idle;
			m_JumpAttackLowLandAccuTime = 0;
		}
		break;
	case Monstro::MonstroState::dying:
		break;
	case Monstro::MonstroState::dead:
		break;
	}

}

void Monstro::DoEnemyCollisions(const std::vector<Enemy*>& roomEnemies, int currentEnemyIndex)
{
}
