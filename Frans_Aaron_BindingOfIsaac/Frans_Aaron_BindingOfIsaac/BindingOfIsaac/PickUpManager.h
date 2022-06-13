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

	PickUpManager(const PickUpManager& rhs) = default;
	PickUpManager(PickUpManager && rhs) = default;
	PickUpManager& operator=(const PickUpManager & rhs) = default;
	PickUpManager& operator=(PickUpManager && rhs) = default;
	~PickUpManager();



	void DrawPickups(Room* currentRoom) const;

	void Update(Room* currentRoom, Isaac* isaac);

	void AddPickUp(Room* currentRoom, const TextureManager& textureManager);

	bool RoomHasPickUps(Room* currentRoom);

private:


	std::map<Room*, std::vector<PickUp*>> m_pPickupsPerRoom;
};

