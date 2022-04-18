#include "pch.h"
#include "Isaac.h"
#include "Texture.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "TearManager.h"
#include "Room.h"
#include "GameObject.h"
#include "IsaacHealthBar.h"
#include "Tear.h"
#include <iostream>


Isaac::Isaac(const TextureManager& textureManager, IsaacHealthBar* isaacHealthBar, const Point2f& centerPosition)
	: m_CenterPosition{ centerPosition }
	, m_BodyDirection{ Isaac::Direction::down }
	, m_HeadDirection{ Isaac::Direction::down }
	, m_Velocity{ 0, 0 }
	, m_WalkSpeed{ 150 }
	, m_TearFireRate{ 1 / 2.0f }
	, m_TearFireAccuSec{ 0 }
	, m_TearSpeed{ 100 }
	, m_TearRange{ 300 }
	, m_BodyState{ BodyState::idle }
	, m_HeadState{ HeadState::idle }
	, m_IdleAccuSec{ 0 }
	, m_pHealth{ isaacHealthBar }
	, m_InvisMaxSec{ 1.5f }
	, m_InvisAccuSec{ 0 }
	, m_DamageState{ DamageState::undamaged }
	, m_Damage{ 3.5 }
{
	m_pHeadSprite = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacHead),
		8, 1, m_TearFireRate / 2.0f, 1, 2 };
	m_pWalkSpriteUD = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacBodyUD),
		10, 1, 1 / 15.0f, 1 };

	m_Width = m_pWalkSpriteUD->GetFrameWidth();
	m_Height = m_pWalkSpriteUD->GetFrameHeight();

	m_pWalkSpriteLR = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacBodyLR),
		10, 1, 1 / 15.0f, 1 };


	m_pHurtSprite = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacHurt),
		1, 1, 1 / 15.0f, 1 };

	m_TearHeight = m_Height / 2.0f + m_pHeadSprite->GetFrameHeight() / 2.0f;
}

Isaac::~Isaac()
{
	delete Isaac::m_pHeadSprite;
	Isaac::m_pHeadSprite = nullptr;
	delete Isaac::m_pWalkSpriteUD;
	Isaac::m_pWalkSpriteUD = nullptr;
	delete Isaac::m_pWalkSpriteLR;
	Isaac::m_pWalkSpriteLR = nullptr;
	delete Isaac::m_pHurtSprite;
	Isaac::m_pHurtSprite = nullptr;
}

void Isaac::Draw() const
{
	switch (m_DamageState)
	{
	case Isaac::DamageState::undamaged:
		DrawBody();
		DrawHead();
		break;
	case Isaac::DamageState::hurt:
		DrawHurt();
		break;
	case Isaac::DamageState::dead:
		DrawDead();
		break;
	}
}

void Isaac::Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager, Room* currentRoom)
{

	switch (m_DamageState)
	{
	case Isaac::DamageState::undamaged:
		UpdateBody(elapsedSec);
		UpdateHead(elapsedSec, tearManager, textureManager);
		UpdatePos(elapsedSec, currentRoom);
		break;
	case Isaac::DamageState::hurt:
		UpdateHurt(elapsedSec);
		UpdatePos(elapsedSec, currentRoom);
		break;
	case Isaac::DamageState::dead:
		UpdateDead(elapsedSec);
		break;
	}
}

void Isaac::TakeDamage(float damage)
{
	if (!IsInvis())
	{
		m_pHealth->TakeDamage(damage);
		switch (m_pHealth->IsDead())
		{
		case true:
			m_DamageState = DamageState::dead;
			break;
		case false:
			m_DamageState = DamageState::hurt;
			break;
		}
	}
}

void Isaac::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
	case SDLK_d:
		m_pWalkSpriteLR->SetActFrame(0);
		m_pWalkSpriteLR->SetAccuSec(0);
		m_BodyDirection = Isaac::Direction::down;
		m_BodyState = BodyState::idle;
		m_Velocity.x = 0;
		break;
	case SDLK_w:
	case SDLK_s:
		m_pWalkSpriteUD->SetActFrame(0);
		m_pWalkSpriteUD->SetAccuSec(0);
		m_BodyDirection = Isaac::Direction::down;
		m_BodyState = BodyState::idle;
		m_BodyState = BodyState::idle;
		m_Velocity.y = 0;
		break;
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_LEFT:
	case SDLK_RIGHT:
		m_pHeadSprite->SetActFrame(0);
		m_pHeadSprite->SetAccuSec(0);
		m_HeadState = HeadState::idle;
		m_TearFireAccuSec = 0;
		break;
	}
}

Point2f Isaac::GetCenter() const
{
	return Point2f{ m_CenterPosition.x, m_CenterPosition.y + m_pHeadSprite->GetFrameHeight() / 2.0f };
}

Rectf Isaac::GetHitBox() const
{
	return Rectf{ m_CenterPosition.x - m_Width / 2.0f,m_CenterPosition.y - m_Height / 2.0f, m_Width, m_Height };
}

void Isaac::DrawBody() const
{
	switch (m_BodyDirection)
	{
	case Isaac::Direction::up:

		m_pWalkSpriteUD->Draw(Point2f{
			m_CenterPosition.x - m_pWalkSpriteUD->GetFrameWidth() / 2.0f,
			m_CenterPosition.y - m_pWalkSpriteUD->GetFrameHeight() / 2.0f
			});

		break;
	case Isaac::Direction::down:

		m_pWalkSpriteUD->Draw(Point2f{
			m_CenterPosition.x - m_pWalkSpriteUD->GetFrameWidth() / 2.0f,
			m_CenterPosition.y - m_pWalkSpriteUD->GetFrameHeight() / 2.0f
			});

		break;
	case Isaac::Direction::left:

		glPushMatrix();

		glTranslatef(m_CenterPosition.x, m_CenterPosition.y, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-m_CenterPosition.x, -m_CenterPosition.y, 0);

		m_pWalkSpriteLR->Draw(Point2f{
			m_CenterPosition.x - m_pWalkSpriteLR->GetFrameWidth() / 2.0f,
			m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f
			});

		glPopMatrix();

		break;
	case Isaac::Direction::right:

		m_pWalkSpriteLR->Draw(Point2f{
			m_CenterPosition.x - m_pWalkSpriteLR->GetFrameWidth() / 2.0f,
			m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f
			});

		break;
	}
}

void Isaac::UpdateBody(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_D] || pStates[SDL_SCANCODE_A])
	{
		m_pWalkSpriteLR->Update(elapsedSec);

	}
	if (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_S])
	{
		m_pWalkSpriteUD->Update(elapsedSec);
	}
	
}

void Isaac::UpdatePos(float elapsedSec, Room* currentRoom)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_D])
	{
		m_BodyDirection = Direction::right;
		m_BodyState = BodyState::walking;
		m_Velocity.x = m_WalkSpeed;

	}
	else if (pStates[SDL_SCANCODE_A])
	{
		m_BodyDirection = Direction::left;
		m_BodyState = BodyState::walking;
		m_Velocity.x = -m_WalkSpeed;
	}

	if (pStates[SDL_SCANCODE_W])
	{
		m_BodyDirection = Direction::up;
		m_BodyState = BodyState::walking;
		m_Velocity.y = m_WalkSpeed;
	}
	else if (pStates[SDL_SCANCODE_S])
	{
		m_BodyDirection = Direction::down;
		m_BodyState = BodyState::walking;
		m_Velocity.y = -m_WalkSpeed;
	}

	if (m_BodyState == BodyState::walking)
	{
		m_CenterPosition.y += m_Velocity.y * elapsedSec;
		m_CenterPosition.x += m_Velocity.x * elapsedSec;
		DoRoomCollision(currentRoom);
		DoGameObjectCollision(currentRoom->GetGameObjects());

	}
}

void Isaac::DoRoomCollision(const Room* currentRoom)
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
		}
		else
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y + hitbox.height / 2.0f;
		}
	}
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), topLeft, topRight, hitInfo) ||
		utils::Raycast(currentRoom->GetWalkableAreaVertices(), bottomRight, bottomLeft, hitInfo))
	{
		if (m_Velocity.x > 0)
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x - hitbox.width / 2.0f;
		}
		else
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x + hitbox.width / 2.0f;
		}
	}
}

void Isaac::DoGameObjectCollision(const std::vector<GameObject*>& objects)
{
	utils::HitInfo hitInfo;
	Rectf hitbox{ GetHitBox() };
	std::vector<Point2f> hitboxPoints{ utils::GetVertices(hitbox) };
	Point2f bottomLeft{ hitboxPoints[0].x -1,  hitboxPoints[0].y - 1 };
	Point2f bottomRight{ hitboxPoints[1].x - 1,  hitboxPoints[1].y - 1 };
	Point2f topRight{ hitboxPoints[2].x - 1,  hitboxPoints[2].y - 1 };
	Point2f topLeft{ hitboxPoints[3].x - 1,  hitboxPoints[3].y - 1 };

	for (GameObject* object : objects)
	{
		if (object->IsNotDestroyed())
		{
			std::vector<Point2f> vertices{ utils::GetVertices(object->GetShape()) };
			if (utils::Raycast(vertices, topRight, bottomRight, hitInfo) ||
				utils::Raycast(vertices, topLeft, bottomLeft, hitInfo))
			{
				if (m_Velocity.y > 0)
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y - hitbox.height / 2.0f;
				}
				else
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y + hitbox.height / 2.0f;
				}
			}
			if (utils::Raycast(vertices, topLeft, topRight, hitInfo) ||
				utils::Raycast(vertices, bottomRight, bottomLeft, hitInfo))
			{
				if (m_Velocity.x > 0)
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x - hitbox.width / 2.0f;
				}
				else
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x + hitbox.width / 2.0f;
				}
			}
		}

	}
}

void Isaac::DrawHead() const
{
	switch (m_HeadDirection)
	{
	case Isaac::Direction::up:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y },

			Point2f{
				m_pHeadSprite->GetFrameWidth() * 4,
				0
			});
		break;
	case Isaac::Direction::down:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y },

			Point2f{
				0,
				0
			});
		break;
	case Isaac::Direction::left:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y },

			Point2f{
				m_pHeadSprite->GetFrameWidth() * 6,
				0
			});
		break;
	case Isaac::Direction::right:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y },

			Point2f{
				m_pHeadSprite->GetFrameWidth() * 2,
				0
			});
		break;
	default:
		break;
	}
}

void Isaac::UpdateHead(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager)
{

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	Vector2f tearVelocity{};
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_TearFireAccuSec += elapsedSec;
		m_HeadDirection = Direction::right;
		m_HeadState = HeadState::shooting;
		m_pHeadSprite->Update(elapsedSec);
		tearVelocity.x = m_TearSpeed;

	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_TearFireAccuSec += elapsedSec;
		m_HeadDirection = Direction::left;
		m_HeadState = HeadState::shooting;
		m_pHeadSprite->Update(elapsedSec);
		tearVelocity.x = -m_TearSpeed;
	}

	if (pStates[SDL_SCANCODE_UP])
	{
		m_TearFireAccuSec += elapsedSec;
		m_HeadDirection = Direction::up;
		m_HeadState = HeadState::shooting;
		m_pHeadSprite->Update(elapsedSec);
		tearVelocity.y = m_TearSpeed;
	}
	else if (pStates[SDL_SCANCODE_DOWN])
	{
		m_TearFireAccuSec += elapsedSec;
		m_HeadDirection = Direction::down;
		m_HeadState = HeadState::shooting;
		m_pHeadSprite->Update(elapsedSec);
		tearVelocity.y = -m_TearSpeed;
	}


	if (m_HeadState == HeadState::idle && m_HeadDirection != Direction::down)
	{
		m_IdleAccuSec += elapsedSec;
		if (m_MaxIdleTime <= m_IdleAccuSec)
		{
			m_HeadDirection = Direction::down;
		}

	}


	if (m_HeadState == HeadState::shooting)
	{
		m_IdleAccuSec = 0;
		Shoot(tearManager, textureManager, tearVelocity);

	}

}

void Isaac::Shoot(TearManager* tearManager, const TextureManager& textureManager, Vector2f tearVelocity)
{
	if (CanShoot())
	{
		m_TearFireAccuSec = 0;
		Tear* pShotTear = tearManager->ShootTear();
		Point2f tearCenterPos;
		bool isFront{ false };
		switch (m_HeadDirection)
		{
		case Direction::up:
			tearCenterPos = Point2f{
					m_CenterPosition.x,
					m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f };
			break;
		case Direction::down:
			tearCenterPos = Point2f{
					m_CenterPosition.x,
					m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f };

			isFront = true;
			break;
		case Direction::left:
			tearCenterPos = Point2f{
					m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
					m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f };
			isFront = true;
			break;
		case Direction::right:
			tearCenterPos = Point2f{
					m_CenterPosition.x + m_pHeadSprite->GetFrameWidth() / 2.0f,
					m_CenterPosition.y - m_pWalkSpriteLR->GetFrameHeight() / 2.0f };
			isFront = true;
			break;
		default:
			break;
		}

		pShotTear->SetTearTexture(textureManager.GetTexture(TextureManager::TextureLookup::isaacTear));
		pShotTear->SetTearHitSprite(textureManager.GetTexture(TextureManager::TextureLookup::isaacTearHit));
		pShotTear->SetTearShape(tearCenterPos, 6);
		pShotTear->SetVelocity(tearVelocity + (m_Velocity / 4.0));
		pShotTear->SetHeight(m_TearHeight);
		pShotTear->SetRange(m_TearRange);
		pShotTear->SetIsFront(isFront);
		pShotTear->SetDamage(m_Damage);
	}
}

void Isaac::DrawHurt() const
{
	m_pHurtSprite->Draw(Point2f{
		m_CenterPosition.x - m_pWalkSpriteUD->GetFrameWidth() / 2.0f,
		m_CenterPosition.y - m_pWalkSpriteUD->GetFrameHeight() / 2.0f
		});
}

void Isaac::UpdateHurt(float elapsedSec)
{
	m_InvisAccuSec += elapsedSec;
	m_pHurtSprite->Update(elapsedSec);
	if (m_InvisAccuSec > m_InvisMaxSec)
	{
		m_InvisAccuSec = 0;
		m_DamageState = DamageState::undamaged;
	}
}

void Isaac::DrawDead() const
{
}

void Isaac::UpdateDead(float elapsedSec)
{
}

bool Isaac::CanShoot()
{
	return m_TearFireAccuSec > m_TearFireRate;
}

bool Isaac::IsInvis()
{
	return m_DamageState != DamageState::undamaged;
}

