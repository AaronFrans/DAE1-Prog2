#pragma once
#include "Door.h"
#include "EnemyManager.h"
#include "TextureManager.h"
#include <vector>
#include <map>
#include <utility>

class Room;
class Isaac;
class RoomManager;
class ItemManager;
class Floor final
{
public:

	enum class TransitionDirection
	{
		up,
		down,
		left,
		right,
	};

	Floor();

	Floor(const Floor& rhs) = default;
	Floor(Floor&& rhs) = default;
	Floor& operator=(const Floor& rhs) = default;
	Floor& operator=(Floor&& rhs) = default;
	~Floor();


	void Draw() const;
	void Update(float elapsedSec, Isaac* isaac, TearManager* tearManager, const TextureManager& textureManager);

	void TranslateCurrentRoomOrigin();

	bool IsTransitioning();
	bool IsDoneTransitioning();
	void DoneTransitioning();
	TransitionDirection GetTransitionDirection();
	float GetTransitionedDistance();

	std::pair<int, int> GetCurrentIndexes();
	int GetMaxRows();
	int GetMaxCols();

	void ActivateDoors();

	Room* GetCurrentRoom();

	void GenerateFloor(RoomManager* roomManager, const TextureManager& textureManager, ItemManager* itemManager);
	void InitEnemies(EnemyManager* enemyManager);

	std::vector<int> GetLayout();

private:

	int m_CurrentRowIndex;
	int m_CurrentColIndex;

	TransitionDirection m_TransitionDirection;
	bool m_IsTransitioning;
	bool m_IsDoneTransitioning;
	float m_TransitionSpeed;
	float m_TransitionedDistance;
	float m_AccuTransitionDistance;
	float m_MaxTransitionDistance;

	static const int m_RoomsCols;
	static const int m_RoomsRows;

	std::vector<Room*> m_pRooms;

	void DrawCurrentRoom() const;
	void DrawTransitioningRoom() const;

	void StarTransition(Door::DoorDirection direction);

	void MoveToNextRoom(Isaac* isaac);

	void PlaceRoom(int currentColIndex, int currentRowIndex, int& NrRooms,
		int maxDirectionDepth, int& directionCurrentDepth, int maxDepth, int& currentDepth, RoomManager* roomManager);

	void PlaceSpecialRooms(RoomManager* roomManager, const TextureManager& textureManager, std::map<int, std::pair<int, Door::DoorDirection>>& indexAndDirectionPairs, ItemManager* itemManager);

	std::map<int, std::pair<int, Door::DoorDirection>> GetAvailableRooms();
};

