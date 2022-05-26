#include "pch.h"
#include "Item.h"
#include "Texture.h"
#include "Sprite.h"
#include "Costume.h"

Item::Item(std::string name, Texture* pickUpTexture, Sprite* costumeUD, Sprite* costumeLR,
	Point2f center, std::map<StatChanges, float> statChanges, CostumeType costumeType)
	: m_Name{ name }
	, m_StatChanges{ statChanges }
	, m_CenterPosition{ center }
{
	m_pPickUpTexture = pickUpTexture;
	m_Width = m_pPickUpTexture->GetWidth();
	m_Height = m_pPickUpTexture->GetHeight();

	Costume::CostumeType type{ (int)costumeType };

	m_pCostume = new Costume(costumeUD, costumeLR, Point2f{ 0,0 }, type);

}

Item::~Item()
{
	delete m_pCostume;
	m_pCostume = nullptr;
}

void Item::SetPosition(Point2f newPos)
{
	m_CenterPosition = newPos;

}

void Item::Draw() const
{
	Rectf drawRect{ m_CenterPosition.x - m_Width / 2.0f, m_CenterPosition.y - m_Height, m_Width, m_Height };
	m_pPickUpTexture->Draw(drawRect);
}

Costume* Item::GetCostume()
{
	return m_pCostume;
}

std::string Item::GetName()
{
	return m_Name;
}

std::map<Item::StatChanges, float> Item::GetStatChanges()
{
	return m_StatChanges;
}
