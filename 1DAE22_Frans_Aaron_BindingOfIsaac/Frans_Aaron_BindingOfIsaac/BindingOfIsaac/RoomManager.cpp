#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "GameObject.h"
#include "Poop.h"
#include "SVGParser.h"
#include <iostream>

//TODO: put m_pRooms functionality in Floor class

RoomManager::RoomManager(const TextureManager& textureManager)
{
	MakeRoomTemplates(textureManager);
}

RoomManager::~RoomManager()
{
	for (Room* room : m_pRoomTemplates)
	{
		delete room;
	}
	for (Room* room : m_pRooms)
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

void RoomManager::MakeRoomTemplates(const TextureManager& textureManager)
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

	if (!SVGParser::GetVerticesFromSvgFile("Resources/SVGs/Rooms/Basement-Room-Big.svg", walkableAreaVertices))
	{
		std::cout << "Could not find SVG File!!!\n";
	}

	MakeBigRooms(textureManager, roomWidth, roomHeight, gameObjectSize, walkableAreaVertices[1]);



}

void RoomManager::MakeStartRoom(const TextureManager& textureManager, const float roomWidth, const float roomHeight, std::vector<Point2f> walkableAreaVertices)
{
	Room* startRoom = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth, roomHeight }, std::vector<GameObject*>{}, walkableAreaVertices);

	m_pRoomTemplates.push_back(startRoom);
}

void RoomManager::MakeSmallRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
			, 5, 1, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	Room* smallRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, walkableAreaVertices);

	objects.clear();


	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f, roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f, roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	Room* smallRoom2 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, walkableAreaVertices);

	objects.clear();

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	Room* smallRoom3 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomSmall
	), Rectf{ 0,0,roomWidth , roomHeight }, objects, walkableAreaVertices);


	m_pRoomTemplates.push_back(smallRoom1);
	m_pRoomTemplates.push_back(smallRoom2);
	m_pRoomTemplates.push_back(smallRoom3);
}

void RoomManager::MakeBigRooms(const TextureManager& textureManager, const float roomWidth, const float roomHeight, const float gameObjectSize, std::vector<Point2f> walkableAreaVertices)
{
	std::vector<GameObject* > objects;

	//bottomleft corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	//topleft corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.25f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.25f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	//topright corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.75f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.75f + gameObjectSize / 2.0f}, gameObjectSize });

	//bottomright corner
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.75f - gameObjectSize / 2.0f, roomHeight * 0.25f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth * 0.75f + gameObjectSize / 2.0f , roomHeight * 0.25f + gameObjectSize / 2.0f}, gameObjectSize });

	//center
	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f - gameObjectSize / 2.0f, roomHeight / 2.0f - gameObjectSize / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f + gameObjectSize / 2.0f , roomHeight / 2.0f + gameObjectSize / 2.0f}, gameObjectSize });

	Room* bigRoom1 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomBig
	), Rectf{ 0,0,roomWidth, roomHeight }, objects, walkableAreaVertices);

	objects.clear();

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
		, 5, 1, Point2f{roomWidth / 2.0f, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f + gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f + gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f - gameObjectSize, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f - gameObjectSize * 2, roomHeight / 2.0f}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f , roomHeight / 2.0f + gameObjectSize * 2}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize}, gameObjectSize });

	objects.push_back(new Poop{ textureManager.GetTexture(TextureManager::TextureLookup::poop)
	, 5, 1, Point2f{roomWidth / 2.0f , roomHeight / 2.0f - gameObjectSize * 2}, gameObjectSize });

	Room* bigRoom2 = new Room(textureManager.GetTexture(
		TextureManager::TextureLookup::roomBig
	), Rectf{ 0,0,roomWidth, roomHeight }, objects, walkableAreaVertices);

	m_pRoomTemplates.push_back(bigRoom1);
	m_pRoomTemplates.push_back(bigRoom2);
}
