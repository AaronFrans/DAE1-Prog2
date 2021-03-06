#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "GameObject.h"
#include "Poop.h"
#include "Rock.h"
#include "SVGParser.h"
#include "EnemyManager.h"
#include "ItemPedestal.h"
#include "SoundEffectManager.h"

#include <iostream>


RoomManager::RoomManager(const TextureManager& textureManager, SoundEffectManager* soundEffectManager)
{
	MakeRoomTemplates(textureManager, soundEffectManager);
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

void RoomManager::MakeRoomTemplates(const TextureManager& textureManager, SoundEffectManager* soundEffectManager)
{

	float roomWidth{ 540 }, roomHeight{ 360 }, gameObjectSize{ 35 };

	std::vector<std::vector<Point2f>> walkableAreaVertices{};
	if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Small.svg", walkableAreaVertices))
	{
		std::cout << "Could not find SVG File!!!\n";
	}


	MakeStartRoom(textureManager, soundEffectManager, roomWidth, roomHeight, walkableAreaVertices[0]);

	MakeItemRoom(textureManager, soundEffectManager, roomWidth, roomHeight, walkableAreaVertices[0], gameObjectSize);

	MakeBossRoom(textureManager, soundEffectManager, roomWidth, roomHeight, walkableAreaVertices[0]);

	MakeSmallRooms(textureManager, soundEffectManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[0]);


	//roomWidth = 1080;
	//roomHeight = 720;

	//if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Big.svg", walkableAreaVertices))
	//{
	//	std::cout << "Could not find SVG File!!!\n";
	//}

	//MakeBigRooms(textureManager, enemyManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[1]);



}

void RoomManager::MakeStartRoom(const TextureManager& textureManager, SoundEffectManager* soundEffectManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices)
{
	SoundEffect* pRoomDoorOpen{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorOpen) };
	SoundEffect* pRoomDoorClosed{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorClose) };

	Room* startRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, std::vector<std::vector<Point2f>>{}, walkableAreaVertices,
		Room::RoomType::starter);

	startRoom->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	startRoom->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	startRoom->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	startRoom->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

	m_pRoomTemplates.push_back(startRoom);
}

void RoomManager::MakeItemRoom(const TextureManager& textureManager, SoundEffectManager* soundEffectManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices, float gameObjectSize)
{
	SoundEffect* pRoomDoorOpen{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorOpen) };
	SoundEffect* pRoomDoorClosed{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorClose) };

	Room* itemRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, std::vector<std::vector<Point2f>>{}, walkableAreaVertices,
		Room::RoomType::item);

	itemRoom->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	itemRoom->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	itemRoom->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	itemRoom->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

	m_pRoomTemplates.push_back(itemRoom);
}

void RoomManager::MakeBossRoom(const TextureManager& textureManager, SoundEffectManager* soundEffectManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices)
{

	std::vector<std::vector<Point2f>> enemyGroupPositions;
	std::vector<Point2f> enemyPositions;

	SoundEffect* pRoomDoorOpen{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorOpen) };
	SoundEffect* pRoomDoorClosed{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorClose) };

	enemyPositions.push_back(Point2f{ roomWidth / 2.0f,
			roomHeight / 2.0f });

	enemyGroupPositions.push_back(enemyPositions);

	Room* bossRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, enemyGroupPositions, walkableAreaVertices,
		Room::RoomType::boss);

	bossRoom->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	bossRoom->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	bossRoom->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	bossRoom->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

	m_pRoomTemplates.push_back(bossRoom);
}

void RoomManager::MakeSmallRooms(const TextureManager& textureManager, SoundEffectManager* soundEffectManager,
	const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;
	std::vector<std::vector<Point2f>> enemyGroupPositions;
	std::vector<Point2f> enemyPositions;
	float wallWidth{ 63 }, wallHeight{ 57 };

	SoundEffect* pPoopDestroyedEffect{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::poopDestroyed)};
	SoundEffect* pRoomDoorOpen{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorOpen)};
	SoundEffect* pRoomDoorClosed{ soundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::doorClose)};

	float enemySpacing{ 20 };


#pragma region FirstRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

#pragma endregion

#pragma region Enemies


	enemyPositions.push_back(Point2f{ wallWidth * 2 + enemySpacing,
			roomHeight - wallHeight * 2 - enemySpacing });

	enemyPositions.push_back(Point2f{ wallWidth * 2 + enemySpacing
		, roomHeight - wallHeight * 2 - enemySpacing * 3 });

	enemyPositions.push_back(Point2f{ wallWidth * 2 + enemySpacing * 5,
		roomHeight - wallHeight * 2 - enemySpacing });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 - enemySpacing * 3,
		0 + wallHeight * 2 + enemySpacing * 3 });

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 - enemySpacing * 3,
		0 + wallHeight * 2 + enemySpacing * 5 });

	enemyPositions.push_back(Point2f{ roomWidth - wallWidth * 2 - enemySpacing * 5,
		0 + wallHeight * 2 + enemySpacing * 3 });

	enemyGroupPositions.push_back(enemyPositions);

	enemyPositions.clear();

#pragma endregion

	Room* smallRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::normal);

	smallRoom1->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	smallRoom1->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });

#pragma endregion

	objects.clear();
	enemyGroupPositions.clear();


#pragma region SecondRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
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
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::normal);

	smallRoom2->PlaceDoor(textureManager, Point2f{ 270, 42 }, Door::DoorDirection::down, Rectf{ 257, 27, 27, 34 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 270, 320 }, Door::DoorDirection::up, Rectf{ 257, 301, 27, 34 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 50, 180 }, Door::DoorDirection::left, Rectf{ 36, 168, 34, 27 });
	smallRoom2->PlaceDoor(textureManager, Point2f{ 495, 180 }, Door::DoorDirection::right, Rectf{ 478, 168, 34, 27 });
#pragma endregion

	objects.clear();
	enemyGroupPositions.clear();

#pragma region ThirdRoom

#pragma region Objects

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop), pPoopDestroyedEffect
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
	), pRoomDoorOpen, pRoomDoorClosed, Rectf{ 0,0,roomWidth , roomHeight }, objects, enemyGroupPositions, walkableAreaVertices, Room::RoomType::normal);

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
