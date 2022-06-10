#pragma once
#include "TextureManager.h"
#include <vector>
#include <utility>

class UiRoom;
class Minimap final
{

public:

	Minimap(const TextureManager& textureManager, std::vector<int> roomLayout,
		std::pair<int, int> startIndexes, int maxnrRows, int maxnrColls);

	Minimap(const Minimap& rhs) = default;
	Minimap(Minimap && rhs) = default;
	Minimap& operator=(const Minimap & rhs) = default;
	Minimap& operator=(Minimap && rhs) = default;
	~Minimap();


	void Draw(const Point2f& topRightPos) const;

	void MoveRoom(std::pair<int, int> newIndexes);

	float GetWidth();
	float GetHeight();

private:

	Texture* m_pMinimapTexture;

	std::vector<UiRoom*> m_pRooms;

	int m_CurrentColIndex;
	int m_CurrentRowIndex;
	int m_MaxNrColls;
	int m_MaxNrRows;


	float m_DrawWidth;
	float m_DrawHeight;

	void InitRooms();
	void MakeSurroundingRoomsVisible();
};

