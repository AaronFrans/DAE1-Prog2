#include "pch.h"
#include "Costume.h"
#include "Sprite.h"

Costume::Costume(Sprite* costumeUD, Sprite* costumeLR, Point2f center, Costume::CostumeType type)
	: m_pCostumeUD{ costumeUD }
	, m_pCostumeLR{ costumeLR }
	, m_CenterPosition{ center }
	, m_Type{ type }
	, m_Direction{Costume::CostumeDirection::down}
{
	m_WidthUD = m_pCostumeUD->GetFrameWidth();
	m_HeightUD = m_pCostumeUD->GetFrameHeight();

	m_WidthLR = m_pCostumeLR->GetFrameWidth();
	m_HeightLR = m_pCostumeLR->GetFrameHeight();


}

Costume::~Costume()
{
	delete m_pCostumeUD;
	m_pCostumeUD = nullptr;
	delete m_pCostumeLR;
	m_pCostumeLR = nullptr;

}

void Costume::SetPosition(Point2f newPos)
{
	m_CenterPosition = newPos;
}

void Costume::Draw() const
{
	Rectf drawRect{};
	switch (m_Direction)
	{
	case Costume::CostumeDirection::up:
	case Costume::CostumeDirection::down:
		drawRect = Rectf{ m_CenterPosition.x - m_WidthUD / 2.0f, m_CenterPosition.y - m_HeightUD / 2.0f, m_WidthUD, m_HeightUD };
		m_pCostumeUD->Draw(drawRect);
		break;
	case Costume::CostumeDirection::left:
	case Costume::CostumeDirection::right:
		drawRect = Rectf{ m_CenterPosition.x - m_WidthLR / 2.0f, m_CenterPosition.y  - m_HeightLR / 2.0f, m_WidthLR, m_HeightLR };
		m_pCostumeLR->Draw(drawRect);
		break;
	}

	
}


void Costume::Update(float elapsedSec) 
{

	if (Costume::CostumeDirection::left == m_Direction|| Costume::CostumeDirection::right == m_Direction)
	{
		m_pCostumeLR->Update(elapsedSec);

	}
	if (Costume::CostumeDirection::up == m_Direction || Costume::CostumeDirection::down == m_Direction)
	{
		m_pCostumeUD->Update(elapsedSec);
	}
}

void Costume::SetDirection(CostumeDirection direction)
{
	m_Direction = direction;
}

Costume::CostumeType Costume::GetType()
{
	return m_Type;
}

void Costume::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
	case SDLK_d:
		m_pCostumeLR->SetActFrame(0);
		m_pCostumeLR->SetAccuSec(0);
		m_Direction = CostumeDirection::down;
		break;
	case SDLK_w:
	case SDLK_s:
		m_pCostumeUD->SetActFrame(0);
		m_pCostumeUD->SetAccuSec(0);
		m_Direction = CostumeDirection::down;
		break;
	}
}
