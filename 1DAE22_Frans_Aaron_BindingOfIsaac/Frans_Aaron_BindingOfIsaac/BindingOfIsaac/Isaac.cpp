#include "pch.h"
#include "Isaac.h"
#include "Texture.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "TearManager.h"
#include "Room.h"
#include "GameObject.h"
#include <iostream>





Isaac::Isaac(const TextureManager& textureManager)
	: Isaac(textureManager, Point2f{ 0,0 })
{
}

Isaac::Isaac(const TextureManager& textureManager, const Point2f& centerPosition)
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
{
	m_pHeadSprite = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacHead),
		8, 1, m_TearFireRate / 2.0f, 1, 2 };
	m_pWalkSpriteUD = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacBodyUD),
		10, 1, 1 / 10.0f, 1 };
	m_pWalkSpriteLR = new Sprite{ textureManager.GetTexture(TextureManager::TextureLookup::isaacBodyLR),
		10, 1, 1 / 10.0f, 1 };


	m_TearHeight = m_pWalkSpriteLR->GetFrameHeight() / 2.0f + m_pHeadSprite->GetFrameHeight() / 2.0f;
}

Isaac::~Isaac()
{
	delete Isaac::m_pHeadSprite;
	Isaac::m_pHeadSprite = nullptr;
	delete Isaac::m_pWalkSpriteUD;
	Isaac::m_pWalkSpriteUD = nullptr;
	delete Isaac::m_pWalkSpriteLR;
	Isaac::m_pWalkSpriteLR = nullptr;
}

void Isaac::Draw() const
{
	DrawBody();
	DrawHead();
}

void Isaac::Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager, Room* currentRoom)
{
	UpdateBody(elapsedSec, currentRoom);
	UpdateHead(elapsedSec, tearManager, textureManager);
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

Point2f Isaac::GetCenter()
{
	return Point2f{ m_CenterPosition.x, m_CenterPosition.y + m_pHeadSprite->GetFrameHeight() / 2.0f };
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

void Isaac::UpdateBody(float elapsedSec, Room* currentRoom)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_D])
	{
		m_BodyDirection = Direction::right;
		m_BodyState = BodyState::walking;
		m_Velocity.x = m_WalkSpeed;
		m_pWalkSpriteLR->Update(elapsedSec);

	}
	else if (pStates[SDL_SCANCODE_A])
	{
		m_BodyDirection = Direction::left;
		m_BodyState = BodyState::walking;
		m_Velocity.x = -m_WalkSpeed;
		m_pWalkSpriteLR->Update(elapsedSec);
	}

	if (pStates[SDL_SCANCODE_W])
	{
		m_BodyDirection = Direction::up;
		m_BodyState = BodyState::walking;
		m_Velocity.y = m_WalkSpeed;
		m_pWalkSpriteUD->Update(elapsedSec);
	}
	else if (pStates[SDL_SCANCODE_S])
	{
		m_BodyDirection = Direction::down;
		m_BodyState = BodyState::walking;
		m_Velocity.y = -m_WalkSpeed;
		m_pWalkSpriteUD->Update(elapsedSec);
	}
	UpdatePos(elapsedSec, currentRoom);
}

void Isaac::UpdatePos(float elapsedSec, Room* currentRoom)
{
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
	float bodyHeight{ m_pWalkSpriteUD->GetFrameHeight() }, bodyWidth{ m_pWalkSpriteUD->GetFrameWidth() };
	Point2f isaacHitboxBottom{ m_CenterPosition.x,  m_CenterPosition.y - bodyHeight / 2.0f };
	Point2f isaacHitboxTop{ m_CenterPosition.x,  m_CenterPosition.y + bodyHeight / 2.0f };
	Point2f isaacHitboxLeft{ m_CenterPosition.x - bodyWidth / 2.0f,  m_CenterPosition.y };
	Point2f isaacHitboxRight{ m_CenterPosition.x + bodyWidth / 2.0f,  m_CenterPosition.y };
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), isaacHitboxTop, isaacHitboxBottom, hitInfo))
	{
		if (m_Velocity.y > 0)
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y - bodyHeight / 2.0f;
		}
		else
		{
			m_CenterPosition.y = hitInfo.intersectPoint.y + bodyHeight / 2.0f;
		}
	}
	if (utils::Raycast(currentRoom->GetWalkableAreaVertices(), isaacHitboxLeft, isaacHitboxRight, hitInfo))
	{
		if (m_Velocity.x > 0)
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x - bodyWidth / 2.0f;
		}
		else
		{
			m_CenterPosition.x = hitInfo.intersectPoint.x + bodyWidth / 2.0f;
		}
	}
}

void Isaac::DoGameObjectCollision(const std::vector<GameObject*>& objects)
{
	utils::HitInfo hitInfo;
	float bodyHeight{ m_pWalkSpriteUD->GetFrameHeight() }, bodyWidth{ m_pWalkSpriteUD->GetFrameWidth() };
	Point2f isaacHitboxBottom{ m_CenterPosition.x,  m_CenterPosition.y - bodyHeight / 2.0f };
	Point2f isaacHitboxTop{ m_CenterPosition.x,  m_CenterPosition.y + bodyHeight / 2.0f };
	Point2f isaacHitboxLeft{ m_CenterPosition.x - bodyWidth / 2.0f,  m_CenterPosition.y };
	Point2f isaacHitboxRight{ m_CenterPosition.x + bodyWidth / 2.0f,  m_CenterPosition.y };
	for (GameObject* object : objects)
	{
		if (object->IsNotDestroyed())
		{
			std::vector<Point2f> vertices{ utils::GetVertices(object->GetShape()) };
			if (utils::Raycast(vertices, isaacHitboxTop, isaacHitboxBottom, hitInfo))
			{
				if (m_Velocity.y > 0)
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y - bodyHeight / 2.0f;
				}
				else
				{
					m_CenterPosition.y = hitInfo.intersectPoint.y + bodyHeight / 2.0f;
				}
			}
			if (utils::Raycast(vertices, isaacHitboxLeft, isaacHitboxRight, hitInfo))
			{
				if (m_Velocity.x > 0)
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x - bodyWidth / 2.0f;
				}
				else
				{
					m_CenterPosition.x = hitInfo.intersectPoint.x + bodyWidth / 2.0f;
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
		pShotTear->SetTearShape(tearCenterPos, 10);
		pShotTear->SetVelocity(tearVelocity + (m_Velocity / 4.0));
		pShotTear->SetHeight(m_TearHeight);
		pShotTear->SetRange(m_TearRange);
		pShotTear->SetIsFront(isFront);
	}
}

bool Isaac::CanShoot()
{
	return m_TearFireAccuSec > m_TearFireRate;
}


//void Isaac::SetState(BodyState bodyState)
//{
//	m_BodyDirection = bodyState;
//}
