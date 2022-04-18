#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "GameObject.h"
#include "Poop.h"
#include "Rock.h"
#include "SVGParser.h"
#include <iostream>
#include "EnemyManager.h"

//TODO: put m_pRooms functionality in Floor class

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

	MakeSmallRooms(textureManager, enemyManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[0]);


	roomWidth = 1080;
	roomHeight = 720;

	if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Big.svg", walkableAreaVertices))
	{
		std::cout << "Could not find SVG File!!!\n";
	}

	MakeBigRooms(textureManager, enemyManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[1]);



}

void RoomManager::MakeStartRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices)
{
	Room* startRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, std::vector<Enemy*>{}, walkableAreaVertices);

	m_pRoomTemplates.push_back(startRoom);
}

void RoomManager::MakeSmallRooms(const TextureManager& textureManager, const EnemyManager& enemyManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;
	std::vector<Enemy*> enemies;

	float wallWidth{ 63 }, wallHeight{ 57 };

	Enemy* pRandomEnemy{ nullptr };
	Circlef enemyShape{ };
	Enemy* pEnemy{ nullptr };

#pragma region FirstRoom
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

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ 0 + wallWidth * 2 + enemyShape.radius,
			roomHeight - wallHeight * 2 - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ 0 + wallWidth * 2 + enemyShape.radius
		, roomHeight - wallHeight * 2 - enemyShape.radius * 5 });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ 0 + wallWidth * 2 + enemyShape.radius * 5,
		roomHeight - wallHeight * 2 - enemyShape.radius });
	enemies.push_back(pEnemy->clone());


	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth - wallWidth * 2 + enemyShape.radius * 3,
		0 + wallHeight * 2 - enemyShape.radius * 3 });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth - wallWidth * 2 + enemyShape.radius * 3,
		0 + wallHeight * 2 - enemyShape.radius * 5 });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth - wallWidth * 2 + enemyShape.radius * 5,
		0 + wallHeight * 2 - enemyShape.radius * 3 });
	enemies.push_back(pEnemy->clone());


	Room* smallRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemies, walkableAreaVertices);

#pragma endregion

	enemies.clear();
	objects.clear();


#pragma region SecondRoom
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

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f });
	enemies.push_back(pEnemy->clone());

	Room* smallRoom2 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemies, walkableAreaVertices);
#pragma endregion

	objects.clear();
	enemies.clear();

#pragma region ThirdRoom
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


	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius * 2, roomHeight / 2.0f });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius * 2, roomHeight / 2.0f });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f + enemyShape.radius * 2 });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f, roomHeight / 2.0f - enemyShape.radius * 2 });
	enemies.push_back(pEnemy->clone());

	Room* smallRoom3 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, enemies, walkableAreaVertices);

#pragma endregion

	pRandomEnemy = nullptr;
	pEnemy = nullptr;

	objects.clear();
	enemies.clear();

	m_pRoomTemplates.push_back(smallRoom1);
	m_pRoomTemplates.push_back(smallRoom2);
	m_pRoomTemplates.push_back(smallRoom3);
}

void RoomManager::MakeBigRooms(const TextureManager& textureManager, const EnemyManager& enemyManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;
	std::vector<Enemy*> enemies;

	float wallWidth{ 63 }, wallHeight{ 57 };

	Enemy* pRandomEnemy{ nullptr };
	Circlef enemyShape{ };
	Enemy* pEnemy{ nullptr };

#pragma region FirstRoom

	//bottomleft corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	//topleft corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	//topright corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	//bottomright corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	//center
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f - gameObjectSize / 2.0f, roomHeight / 2.0f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f + gameObjectSize / 2.0f , roomHeight / 2.0f + gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f + gameObjectSize / 2.0f, roomHeight / 2.0f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f - gameObjectSize / 2.0f , roomHeight / 2.0f + gameObjectSize / 2.0f}, gameObjectSize });

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight / 2.0f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight / 2.0f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth / 2.0f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	Room* bigRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomBig
	), Rectf{ 0,0,roomWidth, roomHeight }, objects, enemies, walkableAreaVertices);

#pragma endregion

	enemies.clear();
	objects.clear();

#pragma region SecondRoom

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f + gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f - gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize * 2}, gameObjectSize });

	objects.push_back(new Rock{ textureManager.GetTexture(TextureManager::TextureLookup::rock)
		, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize * 2}, gameObjectSize });


	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();
	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();
	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.25f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.25f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();
	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.25f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
	pEnemy = pRandomEnemy;
	enemyShape = pEnemy->GetHitBox();
	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.75f - enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f + enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	pEnemy->SetPosition(Point2f{ roomWidth * 0.75f - enemyShape.radius, roomHeight * 0.75f + enemyShape.radius });
	enemies.push_back(pEnemy->clone());

	Room* bigRoom2 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomBig
	), Rectf{ 0,0,roomWidth, roomHeight }, objects, enemies, walkableAreaVertices);

#pragma endregion

	enemies.clear();
	objects.clear();

	pRandomEnemy = nullptr;
	pEnemy = nullptr;


	m_pRoomTemplates.push_back(bigRoom1);
	m_pRoomTemplates.push_back(bigRoom2);
}
