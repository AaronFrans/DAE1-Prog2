#pragma once
#include <map>
#include <vector>
class Room;
class PickUp;
class Isaac;
class TextureManager;
class PickUpManager
{

public:
	PickUpManager();


	void DrawPickups(Room* currentRoom) const;

	void Update(Room* currentRoom, Isaac* isaac);

	void AddPickUp(Room* currentRoom, const TextureManager& textureManager);

	bool RoomHasPickUps(Room* currentRoom);

private:


	std::map<Room*, std::vector<PickUp*>> m_pPickupsPerRoom;
};

