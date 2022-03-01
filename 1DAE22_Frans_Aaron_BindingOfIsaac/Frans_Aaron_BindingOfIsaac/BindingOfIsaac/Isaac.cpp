#include "pch.h"
#include "Isaac.h"
#include "Texture.h"
#include "Sprite.h"

Sprite* Isaac::m_pHeadSprite{ nullptr };
Sprite* Isaac::m_pWalkSpriteUD{ nullptr };
Sprite* Isaac::m_pWalkSpriteLR{ nullptr };

Isaac::Isaac()
	: Isaac(Point2f{ 0,0 })
{
}

Isaac::Isaac(const Point2f& centerPosition)
	: m_CenterPosition{ centerPosition }
	, m_BodyState{ Isaac::Direction::down }
	, m_HeadState{ Isaac::Direction::down }
	, m_Velocity{ 150, 150 }
{
	m_pHeadSprite = new Sprite{ "Resources/Images/Isaac/Isaac-Head.png", 8, 1, 1 / 10.0f, 1 , 2};
	m_pWalkSpriteUD = new Sprite{ "Resources/Images/Isaac/Isaac-Walk-UD.png", 10, 1, 1 / 10.0f, 1 };
	m_pWalkSpriteLR = new Sprite{ "Resources/Images/Isaac/Isaac-Walk-LR.png", 10, 1, 1 / 10.0f, 1 };

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

void Isaac::Update(float elapsedSec)
{
	UpdateBody(elapsedSec);
	UpdateHead(elapsedSec);
}

void Isaac::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
	case SDLK_d:
		m_pWalkSpriteLR->SetActFrame(0);
		m_pWalkSpriteLR->SetAccuSec(0);
		m_BodyState = Isaac::Direction::down;
		break;
	case SDLK_w:
	case SDLK_s:
		m_pWalkSpriteUD->SetActFrame(0);
		m_pWalkSpriteUD->SetAccuSec(0);
		m_BodyState = Isaac::Direction::down;
		break;
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_LEFT:
	case SDLK_RIGHT:
		m_pHeadSprite->SetActFrame(0);
		m_pHeadSprite->SetAccuSec(0);
		m_HeadState = Isaac::Direction::down;
		break;
	}
}

void Isaac::DrawBody() const
{

	switch (m_BodyState)
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

	if (pStates[SDL_SCANCODE_D])
	{
		m_BodyState = Direction::right;
		m_CenterPosition.x += m_Velocity.x * elapsedSec;
		m_pWalkSpriteLR->Update(elapsedSec);

	}
	else if (pStates[SDL_SCANCODE_A])
	{
		m_BodyState = Direction::left;
		m_CenterPosition.x -= m_Velocity.x * elapsedSec;
		m_pWalkSpriteLR->Update(elapsedSec);
	}

	if (pStates[SDL_SCANCODE_W])
	{
		m_BodyState = Direction::up;
		m_CenterPosition.y += m_Velocity.y * elapsedSec;
		m_pWalkSpriteUD->Update(elapsedSec);
	}
	else if (pStates[SDL_SCANCODE_S])
	{
		m_BodyState = Direction::down;
		m_CenterPosition.y -= m_Velocity.y * elapsedSec;
		m_pWalkSpriteUD->Update(elapsedSec);
	}
}

void Isaac::DrawHead() const
{
	switch (m_HeadState)
	{
	case Isaac::Direction::up:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y},

			Point2f{
				m_pHeadSprite->GetFrameWidth() * 4,
				0
			});
		break;
	case Isaac::Direction::down:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y},

			Point2f{
				0,
				0
			});
		break;
	case Isaac::Direction::left:
		m_pHeadSprite->Draw(Point2f{
			m_CenterPosition.x - m_pHeadSprite->GetFrameWidth() / 2.0f,
			m_CenterPosition.y},

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

void Isaac::UpdateHead(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_HeadState = Direction::right;
		m_pHeadSprite->Update(elapsedSec);

	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_HeadState = Direction::left;
		m_pHeadSprite->Update(elapsedSec);
	}

	if (pStates[SDL_SCANCODE_UP])
	{
		m_HeadState = Direction::up;
		m_pHeadSprite->Update(elapsedSec);
	}
	else if (pStates[SDL_SCANCODE_DOWN])
	{
		m_HeadState = Direction::down;
		m_pHeadSprite->Update(elapsedSec);
	}
}

//void Isaac::SetState(BodyState bodyState)
//{
//	m_BodyState = bodyState;
//}
