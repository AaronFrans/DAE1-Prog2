#pragma once
#include <vector>
#include "TextureManager.h"
#include "EnemyManager.h"

class Room;
class RoomManager final
{

public:

	enum class RoomLookup
	{
		startRoom = 0,
		itemRoom,
		bossRoom,
		smallRoom1,
		smallRoom2,
		smallRoom3,
		count
	};

	RoomManager(const TextureManager& textureManager, const EnemyManager& enemyManager);

	RoomManager(const RoomManager& rhs) = default;
	RoomManager(RoomManager && rhs) = default;
	RoomManager& operator=(const RoomManager & rhs) = default;
	RoomManager& operator=(RoomManager && rhs) = default;
	~RoomManager();


	Room* GetRoom(RoomLookup lookup) const;


private:
	std::vector<Room*> m_pRoomTemplates;

	void MakeRoomTemplates(const TextureManager& textureManager, const EnemyManager& enemyManager);

	void MakeStartRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices);
	void MakeItemRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices, float gameObjectSize);
	void MakeBossRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices);
	void MakeSmallRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices);
	//void MakeBigRooms(const TextureManager& textureManager, const EnemyManager& enemyManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices);
};

