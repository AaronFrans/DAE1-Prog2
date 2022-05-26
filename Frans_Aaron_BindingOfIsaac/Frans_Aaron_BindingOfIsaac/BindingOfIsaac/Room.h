#pragma once
#include "Door.h"
#include "EnemyManager.h"
#include <vector>
#include <map>

class GameObject;
class Texture;
class Enemy;
class Isaac;
class EnemyManager;
class ItemPedestal;
class Item;
class Room
{

public:

	enum class RoomType
	{
		starter,
		normal,
		boss,
		item
	};

	Room(Texture* background, Rectf shape, std::vector<GameObject*> objects,
		std::vector<std::vector<Point2f>> enemyGroupPositions, std::vector<Point2f> walkableAreaVertices,
		RoomType type, bool isCleared = false);

	Room(const Room& rhs);
	Room(Room && rhs) = default;
	Room& operator=(const Room & rhs);
	Room& operator=(Room && rhs) = default;
	~Room();

	void Draw() const;
	void Update(float elapsedSec, Isaac* isaac);


	Rectf GetBoundaries() const;
	std::vector<GameObject*> GetGameObjects() const;
	std::vector<Enemy*> GetEnemies() const;
	size_t GetNrObjects() const;
	std::vector<Point2f> GetWalkableAreaVertices() const;
	std::vector<Door*> GetDoors();
	Rectf GetDoorShape(Door::DoorDirection direction);
	bool IsCleared() const;
	RoomType GetType() const;
	std::vector<ItemPedestal*> GetPedestals();

	void SetOrigin(Point2f origin);

	void PlaceDoor(const TextureManager& textureManager, const Point2f& doorCenter, Door::DoorDirection direction, Rectf shape);
	void ActivateDoor(Door::DoorDirection direction);
	void InitEnemies(const EnemyManager& enemyManager);

	void ChangeDoorType(Door::DoorDirection direction, Door::DoorType type,
		const TextureManager& textureManager);

	void AddPedestal(Item* item, Texture* pedestalTexture);

private:

	Texture* m_pBackground;
	std::vector<GameObject*> m_pObjects;
	std::vector<ItemPedestal*> m_pPedestals;
	std::vector<Enemy*> m_pEnemies;
	std::vector<Point2f> m_WalkableAreaVertices;
	Rectf m_Shape;

	RoomType m_Type;

	std::vector<Door*> m_pDoors;
	std::vector<std::vector<Point2f>> m_EnemyGroupPositions;

	bool m_IsCleared;

	void OpenDoors();
	void CloseDoors();
};

