#include "pch.h"
#include "Floor.h"
#include "Room.h"
#include "Isaac.h"
#include "RoomManager.h"
#include "ItemManager.h"

const int Floor::m_RoomsCols = 9;
const int Floor::m_RoomsRows = 9;

Floor::Floor()
	: m_IsTransitioning{ false }
	, m_IsDoneTransitioning{ false }
	, m_TransitionSpeed{ 500 }
	, m_TransitionedDistance{ 0 }
	, m_AccuTransitionDistance{ 0 }
	, m_MaxTransitionDistance{ 500 }
{
	m_pRooms = std::vector<Room*>{};

	for (int i = 0; i < m_RoomsCols; i++)
	{
		for (int j = 0; j < m_RoomsRows; j++)
		{
			m_pRooms.push_back(nullptr);
		}
	}

	m_CurrentRowIndex = m_RoomsRows / 2;
	m_CurrentColIndex = m_RoomsCols / 2;

}

Floor::~Floor()
{
	for (Room* room : m_pRooms)
	{
		delete room;
		room = nullptr;
	}
}

void Floor::Draw() const
{
	if (!m_IsTransitioning)
	{
		DrawCurrentRoom();
	}
	else
	{
		DrawCurrentRoom();
		DrawTransitioningRoom();
	}
}

void Floor::Update(float elapsedSec, Isaac* isaac, TearManager* tearManager, const TextureManager& textureManager)
{
	if (!m_IsTransitioning)
	{
		for (Door* door : GetCurrentRoom()->GetDoors())
		{
			if (door->IsActive() && GetCurrentRoom()->IsCleared() && utils::IsOverlapping(door->GetShape(), isaac->GetHitBox()))
			{
				std::cout << "Isaac Trough Door\n";
				StarTransition(door->GetDirection());
			}
		}
		if (!m_IsTransitioning)
		{
			GetCurrentRoom()->Update(elapsedSec, isaac, tearManager, textureManager);

			if (!GetCurrentRoom()->AreDoorsOpen() && GetCurrentRoom()->IsCleared())
			{
				GetCurrentRoom()->OpenDoors();
			}
		}

	}
	else
	{
		m_TransitionedDistance = m_TransitionSpeed * elapsedSec;
		m_AccuTransitionDistance += m_TransitionedDistance;
		if (m_MaxTransitionDistance <= m_AccuTransitionDistance)
		{

			std::cout << "At next room\n";
			m_IsDoneTransitioning = true;
			MoveToNextRoom(isaac);
			m_TransitionedDistance = 0;
			m_AccuTransitionDistance = 0;
		}
	}

}

void Floor::TranslateCurrentRoomOrigin()
{
	Rectf Shape{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetBoundaries() };
	glTranslatef(-Shape.left, -Shape.bottom, 0);
}

bool Floor::IsTransitioning()
{
	return m_IsTransitioning;
}

bool Floor::IsDoneTransitioning()
{
	return m_IsDoneTransitioning;
}

void Floor::DoneTransitioning()
{
	m_IsTransitioning = false;
	m_IsDoneTransitioning = false;
}

Floor::TransitionDirection Floor::GetTransitionDirection()
{
	return m_TransitionDirection;
}

float Floor::GetTransitionedDistance()
{
	return m_TransitionedDistance;
}

std::pair<int, int> Floor::GetCurrentIndexes()
{
	return std::pair<int, int>(m_CurrentRowIndex, m_CurrentColIndex);
}

int Floor::GetMaxRows()
{
	return m_RoomsRows;
}

int Floor::GetMaxCols()
{
	return m_RoomsCols;
}

Room* Floor::GetCurrentRoom()
{
	return m_pRooms[m_CurrentRowIndex * m_RoomsCols + m_CurrentColIndex];
}

std::vector<int> Floor::GetLayout()
{
	std::vector<int>layout{};
	Room* current = GetCurrentRoom();
	for (int i = 0; i < m_RoomsRows; i++)
	{
		for (int j = 0; j < m_RoomsCols; j++)
		{
			if (m_pRooms[i * m_RoomsCols + j] == nullptr)
				layout.push_back(9);
			else
			{
				if (m_pRooms[i * m_RoomsCols + j]->GetType() == Room::RoomType::item)
					layout.push_back(1);
				else if (m_pRooms[i * m_RoomsCols + j]->GetType() == Room::RoomType::boss)
					layout.push_back(2);
				else
					layout.push_back(0);
			}
		}

	}

	return layout;
}

void Floor::DrawCurrentRoom() const
{
	m_pRooms[(m_CurrentRowIndex)*m_RoomsRows + m_CurrentColIndex]->Draw(!m_IsTransitioning);
}

void Floor::DrawTransitioningRoom() const
{
	switch (m_TransitionDirection)
	{
	case Floor::TransitionDirection::up:
	{

		Room* nextRoom{ m_pRooms[(m_CurrentRowIndex + 1) * m_RoomsRows + m_CurrentColIndex] };

		nextRoom->Draw(false);
	}
	break;
	case Floor::TransitionDirection::down:
	{
		Room* nextRoom{ m_pRooms[(m_CurrentRowIndex - 1) * m_RoomsRows + m_CurrentColIndex] };

		nextRoom->Draw(false);
	}
	break;
	case Floor::TransitionDirection::left:
	{
		Room* nextRoom{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex - 1] };

		nextRoom->Draw(false);
	}
	break;
	case Floor::TransitionDirection::right:
	{
		Room* nextRoom{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex + 1] };

		nextRoom->Draw(false);
	}
	break;
	}
}

void Floor::StarTransition(Door::DoorDirection direction)
{
	std::cout << "Start the Trans\n";
	switch (direction)
	{
	case Door::DoorDirection::up:
	{
		Room* nextRoom{ m_pRooms[(m_CurrentRowIndex + 1) * m_RoomsRows + m_CurrentColIndex] };

		m_TransitionDirection = TransitionDirection::up;

		float change{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]
			->GetBoundaries()
			.height };
		m_MaxTransitionDistance = change;
		m_TransitionSpeed = change;

		Point2f tempNewOrigin{ 0, change };


		nextRoom->SetOrigin(tempNewOrigin);
	}
	break;
	case Door::DoorDirection::down:
	{
		Room* nextRoom{ m_pRooms[(m_CurrentRowIndex - 1) * m_RoomsRows + m_CurrentColIndex] };

		m_TransitionDirection = TransitionDirection::down;

		float change{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]
			->GetBoundaries()
			.height };

		m_MaxTransitionDistance = change;
		m_TransitionSpeed = change;

		Point2f tempNewOrigin{ 0, -change };


		nextRoom->SetOrigin(tempNewOrigin);
	}
	break;
	case Door::DoorDirection::left:
	{
		Room* nextRoom{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex - 1] };

		m_TransitionDirection = TransitionDirection::left;

		float change{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]
			->GetBoundaries()
			.width };

		m_MaxTransitionDistance = change;
		m_TransitionSpeed = change / 2.0f;

		Point2f tempNewOrigin{ -change, 0 };


		nextRoom->SetOrigin(tempNewOrigin);
	}
	break;
	case Door::DoorDirection::right:
	{

		Room* nextRoom{ m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex + 1] };

		m_TransitionDirection = TransitionDirection::right;

		float change{ m_pRooms[(m_CurrentRowIndex)*m_RoomsRows + m_CurrentColIndex]
			->GetBoundaries()
			.width };

		m_MaxTransitionDistance = change;
		m_TransitionSpeed = change;

		Point2f tempNewOrigin{ change, 0 };


		nextRoom->SetOrigin(tempNewOrigin);
	}
	break;
	}

	m_IsTransitioning = true;

}

void Floor::MoveToNextRoom(Isaac* isaac)
{

	Rectf doorShape{ };
	Circlef isaacShape{};
	Point2f newPos{};
	switch (m_TransitionDirection)
	{
	case Floor::TransitionDirection::up:
		m_CurrentRowIndex += 1;

		m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->SetOrigin(Point2f{ 0, -m_MaxTransitionDistance });

		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::down);

		isaacShape = isaac->GetHitBox();

		newPos = Point2f{ doorShape.left + doorShape.width / 2.0f,
			doorShape.bottom + doorShape.height + (isaacShape.radius + 2) };

		isaac->SetCenter(newPos);
		break;
	case Floor::TransitionDirection::down:
		m_CurrentRowIndex -= 1;

		m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->SetOrigin(Point2f{ 0,m_MaxTransitionDistance });

		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::up);
		isaacShape = isaac->GetHitBox();

		newPos = Point2f{ doorShape.left + doorShape.width / 2.0f,
			doorShape.bottom - (isaacShape.radius + 2) };

		isaac->SetCenter(newPos);
		break;
	case Floor::TransitionDirection::left:
		m_CurrentColIndex -= 1;

		m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->SetOrigin(Point2f{ m_MaxTransitionDistance,0 });

		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::right);

		isaacShape = isaac->GetHitBox();

		newPos = Point2f{ doorShape.left - (isaacShape.radius + 2),
			doorShape.bottom + doorShape.height / 2.0f };

		isaac->SetCenter(newPos);
		break;
	case Floor::TransitionDirection::right:
		m_CurrentColIndex += 1;

		m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->SetOrigin(Point2f{ -m_MaxTransitionDistance,0 });

		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::left);

		isaacShape = isaac->GetHitBox();

		newPos = Point2f{ doorShape.left + doorShape.width + (isaacShape.radius + 2),
			doorShape.bottom + doorShape.height / 2.0f };

		isaac->SetCenter(newPos);
		break;
	}


	if (!m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->IsCleared())
		m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->CloseDoors();

}

void Floor::GenerateFloor(RoomManager* roomManager, const TextureManager& textureManager, ItemManager* itemManager)
{
	//Leave for debugging purposes
	//m_pRooms[m_CurrentRowIndex * m_RoomsCols + m_CurrentColIndex] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::startRoom) };
	//m_pRooms[m_CurrentRowIndex * m_RoomsCols + m_CurrentColIndex + 1] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::smallRoom1) };
	//m_pRooms[m_CurrentRowIndex * m_RoomsCols + m_CurrentColIndex - 1] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::smallRoom1) };
	//std::map<int, std::pair<int, Door::DoorDirection>> indexAndDirectionPairs{ GetAvailableRooms() };
	//PlaceSpecialRooms(roomManager, textureManager, indexAndDirectionPairs, itemManager);



	int depth{ 0 }, directionDepth{ 0 }, nrRooms{ 0 }, minRooms{ 7 };
	while (nrRooms < minRooms)
	{

		PlaceRoom(m_CurrentColIndex, m_CurrentRowIndex, nrRooms,
			5, directionDepth, 20, depth, roomManager);

		std::map<int, std::pair<int, Door::DoorDirection>> indexAndDirectionPairs{ GetAvailableRooms() };

		if (nrRooms > minRooms && indexAndDirectionPairs.size() >= 2)
		{
			PlaceSpecialRooms(roomManager, textureManager, indexAndDirectionPairs, itemManager);
		}
		else
		{
			nrRooms = 0;
			directionDepth = 0;
			depth = 0;
			for (int i = 0; i < m_pRooms.size() - 1; i++)
			{

				if (m_pRooms[i] != nullptr)
				{
					delete m_pRooms[i];
					m_pRooms[i] = nullptr;
				}

			}
			indexAndDirectionPairs.clear();
		}
	}
}

void Floor::InitEnemies(EnemyManager* enemyManager)
{
	for (Room* room : m_pRooms)
	{
		if (room != nullptr)
			room->InitEnemies(enemyManager);
	}
}

void Floor::PlaceRoom(int currentColIndex, int currentRowIndex, int& NrRooms,
	int maxDirectionDepth, int& directionCurrentDepth, int maxDepth, int& currentDepth, RoomManager* roomManager)
{

	if (currentDepth == 0)
	{
		m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::startRoom) };
		NrRooms += 1;
	}
	else
	{
		int roomIndex{ utils::GetRand((int)RoomManager::RoomLookup::smallRoom1, (int)RoomManager::RoomLookup::count - 1) };
		m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex] = new Room{ *roomManager->GetRoom((RoomManager::RoomLookup)roomIndex) };
		NrRooms += 1;
	}


	if (currentDepth == 0)
	{
		while (currentDepth == 0)
		{
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{

				if (currentColIndex - 1 != -1 &&
					m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex - 1] == nullptr)
					PlaceRoom(currentColIndex - 1, currentRowIndex, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{

				if (currentColIndex + 1 != m_RoomsCols &&
					m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex + 1] == nullptr)
					PlaceRoom(currentColIndex + 1, currentRowIndex, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{

				if (currentRowIndex - 1 != -1 &&
					m_pRooms[(currentRowIndex - 1) * m_RoomsCols + currentColIndex] == nullptr)
					PlaceRoom(currentColIndex, currentRowIndex - 1, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{

				if (currentRowIndex + 1 != m_RoomsRows &&
					m_pRooms[(currentRowIndex + 1) * m_RoomsCols + currentColIndex] == nullptr)
					PlaceRoom(currentColIndex, currentRowIndex + 1, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
		}
	}
	else if (currentDepth < maxDepth &&
		directionCurrentDepth < maxDirectionDepth)
	{

		if (utils::GetRand(0, 10) % 2 == 0)
		{

			if (currentColIndex - 1 != -1 &&
				m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex - 1] == nullptr)
				PlaceRoom(currentColIndex - 1, currentRowIndex, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{

			if (currentColIndex + 1 != m_RoomsCols &&
				m_pRooms[currentRowIndex * m_RoomsCols + currentColIndex + 1] == nullptr)
				PlaceRoom(currentColIndex + 1, currentRowIndex, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{

			if (currentRowIndex - 1 != -1 &&
				m_pRooms[(currentRowIndex - 1) * m_RoomsCols + currentColIndex] == nullptr)
				PlaceRoom(currentColIndex, currentRowIndex - 1, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{
			if (currentRowIndex + 1 != m_RoomsRows &&
				m_pRooms[(currentRowIndex + 1) * m_RoomsCols + currentColIndex] == nullptr)
				PlaceRoom(currentColIndex, currentRowIndex + 1, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
	}
}

void Floor::PlaceSpecialRooms(RoomManager* roomManager, const TextureManager& textureManager,
	std::map<int, std::pair<int, Door::DoorDirection>>& indexAndDirectionPairs, ItemManager* itemManager)
{

	int specialIndex{};
	int specialNeighborIndex{};


	Room::RoomType specialType{};
	Door::DoorType newDoorType{};

	Door::DoorDirection neighborToSpecialDirection{};

	int pair{ utils::GetRand(0, (int)indexAndDirectionPairs.size() - 1) };

	specialIndex = indexAndDirectionPairs[pair].first;
	neighborToSpecialDirection = indexAndDirectionPairs[pair].second;
	switch (neighborToSpecialDirection)
	{
	case Door::DoorDirection::up:
		specialNeighborIndex = specialIndex - m_RoomsCols;
		break;
	case Door::DoorDirection::down:
		specialNeighborIndex = specialIndex + m_RoomsCols;
		break;
	case Door::DoorDirection::left:
		specialNeighborIndex = specialIndex + 1;
		break;
	case Door::DoorDirection::right:
		specialNeighborIndex = specialIndex - 1;
		break;
	default:
		break;
	}

	specialType = Room::RoomType::item;
	newDoorType = (Door::DoorType)(int)specialType;

	delete m_pRooms[specialIndex];
	m_pRooms[specialIndex] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::itemRoom) };

	m_pRooms[specialIndex]->AddPedestal(itemManager->GetRandomItem(),
		textureManager.GetTexture(TextureManager::TextureLookup::itemPedestal));

	m_pRooms[specialNeighborIndex]->ChangeDoorType(neighborToSpecialDirection, newDoorType, textureManager);


	int secondPair{ utils::GetRand(0, (int)indexAndDirectionPairs.size() - 1) };

	while (secondPair == pair)
	{
		secondPair = utils::GetRand(0, (int)indexAndDirectionPairs.size() - 1);
	}


	specialIndex = indexAndDirectionPairs[secondPair].first;
	neighborToSpecialDirection = indexAndDirectionPairs[secondPair].second;
	switch (neighborToSpecialDirection)
	{
	case Door::DoorDirection::up:
		specialNeighborIndex = specialIndex - m_RoomsCols;
		break;
	case Door::DoorDirection::down:
		specialNeighborIndex = specialIndex + m_RoomsCols;
		break;
	case Door::DoorDirection::left:
		specialNeighborIndex = specialIndex + 1;
		break;
	case Door::DoorDirection::right:
		specialNeighborIndex = specialIndex - 1;
		break;
	default:
		break;
	}

	specialType = Room::RoomType::boss;
	newDoorType = (Door::DoorType)(int)specialType;

	delete m_pRooms[specialIndex];
	m_pRooms[specialIndex] = new Room{ *roomManager->GetRoom(RoomManager::RoomLookup::bossRoom) };

	m_pRooms[specialNeighborIndex]->ChangeDoorType(neighborToSpecialDirection, newDoorType, textureManager);



}

std::map<int, std::pair<int, Door::DoorDirection>> Floor::GetAvailableRooms()
{
	int nrOfNeighbors{};
	int nrOfPairs{};


	Door::DoorDirection neighborToSpecialDirection{};
	std::map<int, std::pair<int, Door::DoorDirection>> indexAndDirectionPairs;

	for (int i = 0; i < m_RoomsCols; i++)
	{
		for (int j = 0; j < m_RoomsRows; j++)
		{
			nrOfNeighbors = 0;
			if (m_pRooms[i * m_RoomsCols + j] != nullptr && m_pRooms[i * m_RoomsCols + j]->GetType() != Room::RoomType::starter)
			{
				if (j + 1 != m_RoomsCols && m_pRooms[i * m_RoomsCols + j + 1] != nullptr)
				{
					++nrOfNeighbors;
					neighborToSpecialDirection = Door::DoorDirection::left;
				}
				if (j - 1 != -1 && m_pRooms[i * m_RoomsCols + j - 1] != nullptr)
				{
					++nrOfNeighbors;
					neighborToSpecialDirection = Door::DoorDirection::right;
				}
				if (i + 1 != m_RoomsRows && m_pRooms[(i + 1) * m_RoomsCols + j] != nullptr)
				{
					++nrOfNeighbors;
					neighborToSpecialDirection = Door::DoorDirection::down;
				}
				if (i - 1 != -1 && m_pRooms[(i - 1) * m_RoomsCols + j] != nullptr)
				{
					++nrOfNeighbors;
					neighborToSpecialDirection = Door::DoorDirection::up;
				}
			}
			if (nrOfNeighbors == 1)
			{
				indexAndDirectionPairs[nrOfPairs] =
					std::make_pair(i * m_RoomsCols + j, neighborToSpecialDirection);

				nrOfPairs++;
			}
		}
	}

	return indexAndDirectionPairs;

}

void Floor::ActivateDoors()
{
	for (int i = 0; i < m_RoomsCols; i++)
	{
		for (int j = 0; j < m_RoomsRows; j++)
		{
			if (m_pRooms[i * m_RoomsCols + j] != nullptr)
			{
				if (j + 1 != m_RoomsCols && m_pRooms[i * m_RoomsCols + j + 1] != nullptr)
				{
					m_pRooms[i * m_RoomsCols + j]->ActivateDoor(Door::DoorDirection::right);
				}
				if (j - 1 != -1 && m_pRooms[i * m_RoomsCols + j - 1] != nullptr)
				{
					m_pRooms[i * m_RoomsCols + j]->ActivateDoor(Door::DoorDirection::left);
				}
				if (i + 1 != m_RoomsRows && m_pRooms[(i + 1) * m_RoomsCols + j] != nullptr)
				{
					m_pRooms[i * m_RoomsCols + j]->ActivateDoor(Door::DoorDirection::up);
				}
				if (i - 1 != -1 && m_pRooms[(i - 1) * m_RoomsCols + j] != nullptr)
				{
					m_pRooms[i * m_RoomsCols + j]->ActivateDoor(Door::DoorDirection::down);
				}
			}
		}
	}

}
