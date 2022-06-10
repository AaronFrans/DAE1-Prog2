#pragma once
#include "TextureManager.h"

class Texture;
class UiRoom
{
public:

	enum class RoomState
	{
		undiscovered,
		seen,
		visited,
	};

	enum class RoomType
	{
		normal,
		item,
		boss,
	};

	UiRoom(const TextureManager& textureManager, RoomType type);

	void Draw(const Point2f& minimapCenter) const;

	void ChangeState(RoomState state);

	float GetWidth();
	float GetHeight();
	RoomState GetState();

private:

	Texture* m_pRoomTexture;
	Texture* m_pSpecialRoomSymbol;

	RoomState m_State;
	RoomType m_Type;

	float m_RoomDrawWidth;
	float m_RoomDrawHeight;
	float m_ItemDrawWidth;
	float m_ItemDrawHeight;

	void DrawSpecialTexture(const Point2f& center) const;

};

