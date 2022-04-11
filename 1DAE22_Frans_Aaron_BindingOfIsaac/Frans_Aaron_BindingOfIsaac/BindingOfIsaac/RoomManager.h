#pragma once
#include <vector>
#include "TextureManager.h"

class Room;
class RoomManager final
{

public:

	enum class RoomLookup
	{
		startRoom = 0,
		smallRoom1 = 1,
		smallRoom2 = 2,
		smallRoom3 = 3,
		bigRoom1 = 4,
		bigRoom2 = 5,

	};

	RoomManager(const TextureManager& textureManager);
	~RoomManager();


	Room* GetRoom(RoomLookup lookup) const;


private:
	std::vector<Room*> m_pRoomTemplates;
	std::vector<Room*> m_pRooms;

	void MakeRoomTemplates(const TextureManager& textureManager);

	void MakeStartRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices);
	void MakeSmallRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices);
	void MakeBigRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices);
};

