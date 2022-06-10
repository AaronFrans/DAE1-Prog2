#include "pch.h"
#include "Minimap.h"
#include "UiRoom.h"
#include "Texture.h"

Minimap::Minimap(const TextureManager& textureManager, std::vector<int> roomLayout,
	std::pair<int, int> startIndexes, int maxnrRows, int maxnrColls)
	: m_CurrentRowIndex{ startIndexes.first }
	, m_CurrentColIndex{ startIndexes.second }
	, m_MaxNrColls{ maxnrColls }
	, m_MaxNrRows{ maxnrRows }
{
	m_pMinimapTexture = textureManager.GetTexture(TextureManager::TextureLookup::uiMinimap);

	m_DrawWidth = m_pMinimapTexture->GetWidth() * 2;
	m_DrawHeight = m_pMinimapTexture->GetHeight() * 2;


	for (int i = 0; i < maxnrRows; i++)
	{

		for (int j = 0; j < maxnrColls; j++)
		{
			switch (roomLayout[i * maxnrColls + j])
			{
			case 0:
				// make normal room
				m_pRooms.push_back(new UiRoom{ textureManager, UiRoom::RoomType::normal });
				break;
			case 1:
				// make item room
				m_pRooms.push_back(new UiRoom{ textureManager, UiRoom::RoomType::item });
				break;
			case 2:
				// make boss room
				m_pRooms.push_back(new UiRoom{ textureManager, UiRoom::RoomType::boss });
				break;
			case 9:
				m_pRooms.push_back(nullptr);
				break;
			}
		}
	}

	InitRooms();

}

Minimap::~Minimap()
{
	for (UiRoom* room : m_pRooms)
	{
		delete room;
	}
}

void Minimap::Draw(const Point2f& topRightPos) const
{
	Rectf dstRect{ topRightPos.x - m_DrawWidth , topRightPos.y - m_DrawHeight, m_DrawWidth, m_DrawHeight };
	m_pMinimapTexture->Draw(dstRect);

	UiRoom* currentRoom{ nullptr };
	int widthOffset{ -3 };
	int heightOffset{ -3 };
	Point2f center{ dstRect.left + m_DrawWidth / 2.0f, dstRect.bottom + m_DrawWidth / 2.0f };
	for (int i = m_CurrentRowIndex - 2; i <= m_CurrentRowIndex + 2; i++)
	{
		heightOffset += 1;
		widthOffset = -3;
		for (int j = m_CurrentColIndex - 2; j <= m_CurrentColIndex + 2; j++)
		{
			widthOffset += 1;
			if (i > -1 && i <= m_MaxNrRows && j > -1 && j <= m_MaxNrColls)
			{
				currentRoom = m_pRooms[i * m_MaxNrColls + j];
				if (currentRoom != nullptr)
				{
					currentRoom->Draw(Point2f{
						center.x + widthOffset * currentRoom->GetWidth(),
						center.y + heightOffset * currentRoom->GetHeight()
						});
				}

			}

		}
	}
}

void Minimap::MoveRoom(std::pair<int, int> newIndexes)
{
	m_CurrentRowIndex = newIndexes.first;
	m_CurrentColIndex = newIndexes.second;
	m_pRooms[(m_CurrentRowIndex * m_MaxNrColls) + m_CurrentColIndex]->ChangeState(UiRoom::RoomState::visited);
	MakeSurroundingRoomsVisible();
}

float Minimap::GetWidth()
{
	return m_DrawWidth;
}

float Minimap::GetHeight()
{
	return m_DrawHeight;
}

void Minimap::InitRooms()
{


	for (int i = m_CurrentRowIndex - 1; i <= m_CurrentRowIndex + 1; i++)
	{
		for (int j = m_CurrentColIndex - 1; j <= m_CurrentColIndex + 1; j++)
		{
			if (m_pRooms[(i * m_MaxNrColls) + j] != nullptr)
			{
				if (i % 2 == 0 && j % 2 == 0)
				{
					m_pRooms[(i * m_MaxNrColls) + j]->ChangeState(UiRoom::RoomState::visited);
				}
				else if (i % 2 == 0 || j % 2 == 0)
				{
					m_pRooms[(i * m_MaxNrColls) + j]->ChangeState(UiRoom::RoomState::seen);
				}
			}


		}
	}


}

void Minimap::MakeSurroundingRoomsVisible()
{

#pragma region AboveRoom
	
	if (m_pRooms[(m_CurrentRowIndex + 1) * m_MaxNrColls + m_CurrentColIndex] != nullptr &&
		m_pRooms[(m_CurrentRowIndex + 1) * m_MaxNrColls + m_CurrentColIndex]->GetState() == UiRoom::RoomState::undiscovered)
		m_pRooms[(m_CurrentRowIndex + 1) * m_MaxNrColls + m_CurrentColIndex]->ChangeState(UiRoom::RoomState::seen);

#pragma endregion

#pragma region BelowRoom

	if (m_pRooms[(m_CurrentRowIndex - 1) * m_MaxNrColls + m_CurrentColIndex] != nullptr &&
		m_pRooms[(m_CurrentRowIndex - 1) * m_MaxNrColls + m_CurrentColIndex]->GetState() == UiRoom::RoomState::undiscovered)
		m_pRooms[(m_CurrentRowIndex - 1) * m_MaxNrColls + m_CurrentColIndex]->ChangeState(UiRoom::RoomState::seen);

#pragma endregion


#pragma region RightRoom

	if (m_pRooms[(m_CurrentRowIndex * m_MaxNrColls) + m_CurrentColIndex + 1] != nullptr &&
		m_pRooms[(m_CurrentRowIndex * m_MaxNrColls) + m_CurrentColIndex + 1]->GetState() == UiRoom::RoomState::undiscovered)
		m_pRooms[(m_CurrentRowIndex * m_MaxNrColls) + m_CurrentColIndex + 1]->ChangeState(UiRoom::RoomState::seen);

#pragma endregion

#pragma region RightRoom

	if (m_pRooms[(m_CurrentRowIndex * m_MaxNrColls ) + m_CurrentColIndex - 1] != nullptr &&
		m_pRooms[(m_CurrentRowIndex * m_MaxNrColls ) + m_CurrentColIndex - 1]->GetState() == UiRoom::RoomState::undiscovered)
		m_pRooms[(m_CurrentRowIndex * m_MaxNrColls ) + m_CurrentColIndex - 1]->ChangeState(UiRoom::RoomState::seen);

#pragma endregion
}
