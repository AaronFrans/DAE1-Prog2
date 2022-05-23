#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "GameObject.h"
#include "Poop.h"
#include "Rock.h"
#include "SVGParser.h"
#include <iostream>
#include "EnemyManager.h"


RoomManager::RoomManager(const TextureManager& textureManager, const EnemyManager& enemyManager)
{
	MakeRoomTemplates(textureManager, enemyManager);
}

RoomManager::~RoomManager()
{
	for (Room* room : m_pRoomTemplates)
	{
		delete room;
	}
}

Room* RoomManager::GetRoom(RoomLookup lookup) const
{
	if ((int)lookup > m_pRoomTemplates.size() - 1)
	{
		return nullptr;
	}
	return m_pRoomTemplates[(int)lookup];
}

void RoomManager::MakeRoomTemplates(const TextureManager& textureManager, const EnemyManager& enemyManager)
{

	float roomWidth{ 540 }, roomHeight{ 360 }, gameObjectSize{ 35 };

	std::vector<std::vector<Point2f>> walkableAreaVertices{};
	if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Small.svg", walkableAreaVertices))
	{
		std::cout << "Could not find SVG File!!!\n";
	}


	MakeStartRoom(textureManager, roomWidth, roomHeight, walkableAreaVertices[0]);

	MakeSmallRooms(textureManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[0]);


	roomWidth = 1080;
	roomHeight = 720;

	//if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Big.svg", walkableAreaVertices))
	//{
	//	std::cout << "Could not find SVG File!!!\n";
	//}

	//MakeBigRooms(textureManager, enemyManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[1]);



}

void RoomManager::MakeStartRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices)
{
	Room* startRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
		), Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, std::vector<std::vector<Point2f>>{}, walkableAreaVertices,
		Room::RoomType::small, true);

	startRoom->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	startRoom->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	startRoom->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	startRoom->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

	m_pRoomTemplates.push_back(startRoom);
}

void RoomManager::MakeSmallRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;
	std::vector<std::vector<Point2f>> enemyGroupPositions;
	std::vector<Point2f> enemyPositions;
	float wallWidth{ 63 }, wallHeight{ 57 };

	float enemySpacing{ 20 };


#pragma region FirstRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

#pragma endregion

#pragma region Enemies

	//move inside floort

	//pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	//pEnemy = pRandomEnemy;
	//enemyShape = pEnemy->GetHitBox();

	//pEnemy->SetPosition(Point2f{ roomWidth - wallWidth * 2 + enemyShape.radius * 3,
	//	0 + wallHeight * 2 - enemyShape.radius * 3 });
	//enemies.push_back(pEnemy->Clone());

	enemyPositions.push_back(Point2f{ 0 + wallWidth * 2 + enemySpacing,
			roomHeight - wallHeight * 2 - enemySpacing });

	enemyPositions.push_back(Point2f{ 0 + wallWidth * 2 + enemySpacing
		, roomHeight - wallHeight * 2 - enemySpacing * 5 });

	enemyPositions.push_back(Point2f{ 0 + wallWidth * 2 + enemySpacing * 5,
		roomHeight - wallHeight * 2 - enemySpacing });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 + enemySpacing * 3,
		0 + wallHeight * 2 - enemySpacing * 3 });

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 + enemySpacing * 3,
		0 + wallHeight * 2 - enemySpacing * 5 });

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 + enemySpacing * 5,
		0 + wallHeight * 2 - enemySpacing * 3 });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();

#pragma endregion

	Room* smallRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::small);

	smallRoom1->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

#pragma endregion

	objects.clear();
	enemyGroupPositions.clear();


#pragma region SecondRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

#pragma endregion

#pragma region Enemies
	enemyPositions.push_back(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();

#pragma endregion

	Room* smallRoom2 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::small);

	smallRoom2->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });
#pragma endregion

	objects.clear();
	enemyGroupPositions.clear();

#pragma region ThirdRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });


	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize / 2.0f, 0 + wallHeight + gameObjectSize / 2.0f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize / 2.0f, 0 + wallHeight + gameObjectSize * 1.5f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize * 1.5f, 0 + wallHeight + gameObjectSize / 2.0f}, gameObjectSize });


	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize / 2.0f, roomHeight - wallHeight - gameObjectSize / 2.0f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize / 2.0f, roomHeight - wallHeight - gameObjectSize * 1.5f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize * 1.5f, roomHeight - wallHeight - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize / 2.0f, roomHeight - wallHeight - gameObjectSize / 2.0f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize / 2.0f, roomHeight - wallHeight - gameObjectSize * 1.5f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{0 + wallWidth + gameObjectSize * 1.5f, roomHeight - wallHeight - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize / 2.0f, 0 + wallHeight + gameObjectSize / 2.0f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize / 2.0f, 0 + wallHeight + gameObjectSize * 1.5f}, gameObjectSize });
	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth - wallWidth - gameObjectSize * 1.5f, 0 + wallHeight + gameObjectSize / 2.0f}, gameObjectSize });

#pragma endregion

#pragma region Enemies

	enemyPositions.push_back(Point2f{ roomWidth / 2.0f + enemySpacing * 2, roomHeight / 2.0f });

	enemyPositions.push_back(Point2f{ roomWidth / 2.0f - enemySpacing * 2, roomHeight / 2.0f });

	enemyPositions.push_back(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f + enemySpacing * 2 });

	enemyPositions.push_back(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f - enemySpacing * 2 });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();


#pragma endregion

	Room* smallRoom3 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::small);

	smallRoom3->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	smallRoom3->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	smallRoom3->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	smallRoom3->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

#pragma endregion

	objects.clear();
	enemyGroupPositions.clear();

	m_pRoomTemplates.push_back(smallRoom1);
	m_pRoomTemplates.push_back(smallRoom2);
	m_pRoomTemplates.push_back(smallRoom3);
}

//void RoomManager::MakeBigRooms(const TextureManager& textureManager, const EnemyManager& enemyManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
//{
//	std::vector<GameObject* > objects;
//	std::vector<Enemy*> enemies;
//
//	float wallWidth{ 63 }, wallHeight{ 57 };
//
//	Enemy* pRandomEnemy{ nullptr };
//	Circlef enemyShape{ };
//	Enemy* pEnemy{ nullptr };
//
//#pragma region FirstRoom
//
//	//bottomleft corner
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	//topleft corner
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	//topright corner
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	//bottomright corner
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	//center
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f - gameObjectSize / 2.0f, roomHeight / 2.0f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f + gameObjectSize / 2.0f , roomHeight / 2.0f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f + gameObjectSize / 2.0f, roomHeight / 2.0f - gameObjectSize / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f - gameObjectSize / 2.0f , roomHeight / 2.0f + gameObjectSize / 2.0f}, gameObjectSize });
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	Room* bigRoom1 = new Room(textureManager.GetTexture(
//		TextureManager::TextureLookup::roomBig
//	), Rectf{ 0,0,roomWidth, roomHeight }, objects, enemies, walkableAreaVertices, Room::RoomType::big);
//
//#pragma endregion
//
//	enemies.clear();
//	objects.clear();
//
//#pragma region SecondRoom
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f + gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f - gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize * 2}, gameObjectSize });
//
//	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
//		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize}, gameObjectSize });
//
//	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
//		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize * 2}, gameObjectSize });
//
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
//	pEnemy = pRandomEnemy;
//	enemyShape = pEnemy->GetHitBox();
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
//	enemies.push_back(pEnemy->Clone());
//
//	Room* bigRoom2 = new Room(textureManager.GetTexture(
//		TextureManager::TextureLookup::roomBig
//	), Rectf{ 0,0,roomWidth, roomHeight }, objects, enemies, walkableAreaVertices, Room::RoomType::big);
//
//#pragma endregion
//
//	enemies.clear();
//	objects.clear();
//
//	pRandomEnemy = nullptr;
//	pEnemy = nullptr;
//
//
//	m_pRoomTemplates.push_back(bigRoom1);
//	m_pRoomTemplates.push_back(bigRoom2);
//}
