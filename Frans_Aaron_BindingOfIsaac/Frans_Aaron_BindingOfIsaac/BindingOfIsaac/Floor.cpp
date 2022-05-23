#include "pch.h"
#include "Floor.h"
#include "Room.h"
#include "Isaac.h"
#include "RoomManager.h"

const int Floor::m_RoomsCols = 9;
const int Floor::m_RoomsRows = 9;

Floor::Floor()
	: m_IsTransitioning{ false }
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
	DrawCurrentRoom();
}

void Floor::Update(float elapsedSec, Isaac* isaac)
{
	for (Door* door : GetCurrentRoom()->GetDoors())
	{
		if (door->IsActive() && GetCurrentRoom()->IsCleared() && utils::IsOverlapping(door->GetShape(), isaac->GetHitBox()))
		{
			m_IsTransitioning = true;
			MoveToNextRoom(door->GetDirection(), isaac);
		}
	}
	GetCurrentRoom()->Update(elapsedSec, isaac);
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

void Floor::DoneTransitioning()
{
	m_IsTransitioning = false;
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
				layout.push_back(0);
			else
			{
				if (i * m_RoomsCols + j == m_CurrentRowIndex * m_RoomsCols + m_CurrentColIndex)
					layout.push_back(2);
				else
					layout.push_back(1);
			}
		}

	}

	return layout;
}

void Floor::DrawCurrentRoom() const
{
	m_pRooms[(m_CurrentRowIndex)*m_RoomsRows + m_CurrentColIndex]->Draw();
}

void Floor::MoveToNextRoom(Door::DoorDirection direction, Isaac* isaac)
{
	Rectf doorShape{ };
	Circlef isaacShape{};
	Point2f newPos{};
	switch (direction)
	{
	case Door::DoorDirection::up:
		m_CurrentRowIndex += 1;
		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::down);
		isaacShape = isaac->GetHitBox();
		newPos = Point2f{ doorShape.left + doorShape.width / 2.0f,
			doorShape.bottom + doorShape.height + (isaacShape.radius + 2) };
		isaac->SetCenter(newPos);
		break;
	case Door::DoorDirection::down:
		m_CurrentRowIndex -= 1;
		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::up);
		isaacShape = isaac->GetHitBox();
		newPos = Point2f{ doorShape.left + doorShape.width / 2.0f,
			doorShape.bottom - (isaacShape.radius + 2) };
		isaac->SetCenter(newPos);
		break;
	case Door::DoorDirection::left:
		m_CurrentColIndex -= 1;
		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::right);
		isaacShape = isaac->GetHitBox();
		newPos = Point2f{ doorShape.left - (isaacShape.radius + 2),
			doorShape.bottom + doorShape.height / 2.0f };
		isaac->SetCenter(newPos);
		break;
	case Door::DoorDirection::right:
		m_CurrentColIndex += 1;
		doorShape = m_pRooms[m_CurrentRowIndex * m_RoomsRows + m_CurrentColIndex]->GetDoorShape(Door::DoorDirection::left);
		isaacShape = isaac->GetHitBox();
		newPos = Point2f{ doorShape.left + doorShape.width + (isaacShape.radius + 2),
			doorShape.bottom + doorShape.height / 2.0f };
		isaac->SetCenter(newPos);
		break;
	}

}

void Floor::GenerateFloor(RoomManager* roomManager)
{
	int depth{ 0 }, direction{ 0 }, nrRooms{ 0 }, minRooms{ 7 };
	while (nrRooms < minRooms)
	{

		PlaceRoom(m_CurrentColIndex, m_CurrentRowIndex, 9, 9, nrRooms,
			7, direction, 20, depth, roomManager);
		if (nrRooms < minRooms)
		{
			nrRooms = 0;
			for (Room* room : m_pRooms)
			{
				if (room != nullptr)
				{
					delete room;
					room = nullptr;
				}

			}
		}
	}
}

void Floor::InitEnemies(const EnemyManager& enemyManager)
{
	for (Room* room : m_pRooms)
	{
		if(room != nullptr)
		room->InitEnemies(enemyManager);
	}
}

void Floor::PlaceRoom(int currentColIndex, int currentRowIndex, int maxNrCols, int maxNrRows, int& NrRooms,
	int maxDirectionDepth, int& directionCurrentDepth, int maxDepth, int& currentDepth, RoomManager* roomManager)
{

	if (currentDepth == 0)
	{
		m_pRooms[currentRowIndex * maxNrCols + currentColIndex] = new Room{*roomManager->GetRoom(RoomManager::RoomLookup::startRoom)};
		NrRooms += 1;
	}
	else
	{
		int roomIndex{ utils::GetRand((int)RoomManager::RoomLookup::smallRoom1, (int)RoomManager::RoomLookup::count - 1) };
		m_pRooms[currentRowIndex * maxNrCols + currentColIndex] = new Room{ *roomManager->GetRoom((RoomManager::RoomLookup)roomIndex) };
		NrRooms += 1;
	}


	if (currentDepth == 0)
	{
		while (currentDepth == 0)
		{
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{
				std::cout << "Left: " << '\n'
					<< "Row: " << std::to_string(currentRowIndex) << '\n'
					<< "Col: " << std::to_string(currentColIndex) << '\n' <<'\n';
				if (currentColIndex - 1 != -1 &&
					m_pRooms[currentRowIndex * maxNrCols + currentColIndex - 1] == nullptr)
					PlaceRoom(currentColIndex - 1, currentRowIndex, maxNrCols, maxNrRows, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{
				std::cout << "Right: " << '\n'
					<< "Row: " << std::to_string(currentRowIndex) << '\n'
					<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
				if (currentColIndex + 1 != maxNrCols &&
					m_pRooms[currentRowIndex * maxNrCols + currentColIndex + 1] == nullptr)
					PlaceRoom(currentColIndex + 1, currentRowIndex, maxNrCols, maxNrRows, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{
				std::cout << "Down: " << '\n'
					<< "Row: " << std::to_string(currentRowIndex) << '\n'
					<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
				if (currentRowIndex - 1 != -1 &&
					m_pRooms[(currentRowIndex - 1) * maxNrCols + currentColIndex] == nullptr)
					PlaceRoom(currentColIndex, currentRowIndex - 1, maxNrCols, maxNrRows, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
			directionCurrentDepth = 0;
			if (utils::GetRand(0, 10) % 2 == 0)
			{
				std::cout << "Up: " << '\n'
					<< "Row: " << std::to_string(currentRowIndex) << '\n'
					<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
				if (currentRowIndex + 1 != maxNrRows &&
					m_pRooms[(currentRowIndex + 1) * maxNrCols + currentColIndex] == nullptr)
					PlaceRoom(currentColIndex, currentRowIndex + 1, maxNrCols, maxNrRows, NrRooms,
						maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
			}
		}
	}
	else if (currentDepth < maxDepth &&
		directionCurrentDepth < maxDirectionDepth)
	{

		if (utils::GetRand(0, 10) % 2 == 0)
		{
			std::cout << "Left: " << '\n'
				<< "Row: " << std::to_string(currentRowIndex) << '\n'
				<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
			if (currentColIndex - 1 != -1 &&
				m_pRooms[currentRowIndex * maxNrCols + currentColIndex - 1] == nullptr)
				PlaceRoom(currentColIndex - 1, currentRowIndex, maxNrCols, maxNrRows, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{
			std::cout << "Right: " << '\n'
				<< "Row: " << std::to_string(currentRowIndex) << '\n'
				<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
			if (currentColIndex + 1 != maxNrCols &&
				m_pRooms[currentRowIndex * maxNrCols + currentColIndex + 1] == nullptr)
				PlaceRoom(currentColIndex + 1, currentRowIndex, maxNrCols, maxNrRows, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{
			std::cout << "Down: " << '\n'
				<< "Row: " << std::to_string(currentRowIndex) << '\n'
				<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
			if (currentRowIndex - 1 != -1 &&
				m_pRooms[(currentRowIndex - 1) * maxNrCols + currentColIndex] == nullptr)
				PlaceRoom(currentColIndex, currentRowIndex - 1, maxNrCols, maxNrRows, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
		if (utils::GetRand(0, 10) % 2 == 0)
		{
			std::cout << "Up: " << '\n'
				<< "Row: " << std::to_string(currentRowIndex) << '\n'
				<< "Col: " << std::to_string(currentColIndex) << '\n' << '\n';
			if (currentRowIndex + 1 != maxNrRows &&
				m_pRooms[(currentRowIndex + 1) * maxNrCols + currentColIndex] == nullptr)
				PlaceRoom(currentColIndex, currentRowIndex + 1, maxNrCols, maxNrRows, NrRooms,
					maxDirectionDepth, directionCurrentDepth += 1, maxDepth, currentDepth += 1, roomManager);
		}
	}
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
