#include "pch.h"
#include "UiRoom.h"
#include "Texture.h"

UiRoom::UiRoom(const TextureManager& textureManager, RoomType type)
	: m_State{ RoomState::undiscovered }
	, m_Type{ type }
{

	m_pRoomTexture = textureManager.GetTexture(TextureManager::TextureLookup::uiMinimapRooms);

	m_RoomDrawWidth = m_pRoomTexture->GetWidth() * 2;
	m_RoomDrawHeight = m_pRoomTexture->GetHeight();

	switch (m_Type)
	{
	case UiRoom::RoomType::normal:
		m_pSpecialRoomSymbol = nullptr;
		break;
	case UiRoom::RoomType::item:
		m_pSpecialRoomSymbol = textureManager.GetTexture(TextureManager::TextureLookup::uiMinimapRoomItem);
		m_ItemDrawWidth = m_pSpecialRoomSymbol->GetWidth() * 2;
		m_ItemDrawHeight = m_pSpecialRoomSymbol->GetHeight() * 2;
		break;
	case UiRoom::RoomType::boss:
		m_pSpecialRoomSymbol = textureManager.GetTexture(TextureManager::TextureLookup::uiMinimapRoomBoss);
		m_ItemDrawWidth = m_pSpecialRoomSymbol->GetWidth() * 2;
		m_ItemDrawHeight = m_pSpecialRoomSymbol->GetHeight() * 2;
		break;
	}
}

void UiRoom::Draw(const Point2f& center) const
{
	Rectf dstRect{ center.x - m_RoomDrawWidth / 2.0f,  center.y - m_RoomDrawHeight / 2.0f,
		m_RoomDrawWidth, m_RoomDrawHeight };

	Rectf srcRect{};
	switch (m_State)
	{
	case UiRoom::RoomState::seen:
		srcRect = Rectf{ 0,0, m_RoomDrawWidth / 2, m_RoomDrawHeight / 2 };
		m_pRoomTexture->Draw(dstRect, srcRect);
		DrawSpecialTexture(center);
		break;
	case UiRoom::RoomState::visited:
		srcRect = Rectf{ 0, m_RoomDrawHeight / 2, m_RoomDrawWidth / 2, m_RoomDrawHeight / 2 };
		m_pRoomTexture->Draw(dstRect, srcRect);
		DrawSpecialTexture(center);
		break;
	}



}

void UiRoom::ChangeState(RoomState state)
{
	m_State = state;
}

float UiRoom::GetWidth()
{
	return m_RoomDrawWidth;
}

float UiRoom::GetHeight()
{
	return m_RoomDrawHeight;
}

UiRoom::RoomState UiRoom::GetState()
{
	return m_State;
}

void UiRoom::DrawSpecialTexture(const Point2f& center) const
{
	Rectf dstRect{ center.x - m_ItemDrawWidth / 2.0f,  center.y - m_ItemDrawHeight / 2.0f,
	m_ItemDrawWidth, m_ItemDrawHeight };

	switch (m_Type)
	{
	case UiRoom::RoomType::item:
		m_pSpecialRoomSymbol->Draw(dstRect);
		break;
	case UiRoom::RoomType::boss:
		m_pSpecialRoomSymbol->Draw(dstRect);
		break;
	default:
		break;
	}
}
