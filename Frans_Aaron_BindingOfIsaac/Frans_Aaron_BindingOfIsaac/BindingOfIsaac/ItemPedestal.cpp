#include "pch.h"
#include "ItemPedestal.h"
#include "Texture.h"
#include "Item.h"

ItemPedestal::ItemPedestal(Texture* pedestalTexture, Point2f center, float size)
	: m_pItem{ nullptr }
	, m_Center{ center }
	, m_DrawShape{ center.x - size / 2.0f, center.y - size / 2.0f, size, size }
	, m_IsItemTaken{ false }
{
	m_pTexture = pedestalTexture;
}

ItemPedestal::ItemPedestal(const ItemPedestal& rhs)
{
	m_pTexture = rhs.m_pTexture;
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;
	m_pItem = rhs.m_pItem;
}

ItemPedestal& ItemPedestal::operator=(const ItemPedestal& rhs)
{
	m_pTexture = rhs.m_pTexture;
	m_DrawShape = rhs.m_DrawShape;
	m_Center = rhs.m_Center;
	m_pItem = rhs.m_pItem;

	return *this;
}

ItemPedestal::~ItemPedestal()
{
}

void ItemPedestal::Draw() const
{
	m_pTexture->Draw(m_DrawShape);
	if (m_IsItemTaken == false)
	{
		m_pItem->Draw();
	}
}

Circlef ItemPedestal::GetShape() const
{
	return Circlef{ m_Center, m_DrawShape.height / 2.0f };
}

Point2f ItemPedestal::GetCenter() const
{
	return m_Center;
}

ItemPedestal* ItemPedestal::Clone() const
{
	return new ItemPedestal(*this);
}

void ItemPedestal::PlaceItem(Item* item)
{
	m_pItem = item;
	m_pItem->SetPosition(Point2f{ m_Center.x, m_Center.y + 50 });
}

void ItemPedestal::TakeItem()
{
	m_IsItemTaken = true;
}

Item* ItemPedestal::GetItem()
{
	return m_pItem;
}

bool ItemPedestal::IsItemTaken()
{
	return m_IsItemTaken;
}
