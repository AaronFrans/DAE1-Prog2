#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "Enemy.h"
#include "GameObject.h"


Room::Room(Texture* background, Rectf shape, std::vector<GameObject*> objects,
	std::vector<Enemy*> enemies, std::vector<Point2f> walkableAreaVertices,
	RoomType type, bool isCleared)
	: m_pBackground{ background }
	, m_Shape{ shape }
	, m_pObjects{ objects }
	, m_WalkableAreaVertices{ walkableAreaVertices }
	, m_pEnemies{ enemies }
	, m_Type{ type }
	, m_IsCleared{ isCleared }
{
}


Room::~Room()
{
	for (GameObject* object : m_pObjects)
	{
		delete object;
	}
	for (Enemy* enemy : m_pEnemies)
	{
		delete enemy;
	}
	for (Door* door : m_pDoors)
	{
		delete door;
	}

}

void Room::Draw() const
{
	m_pBackground->Draw(m_Shape);

	for (Door* door : m_pDoors)
	{
		door->Draw();
	}

	for (GameObject* object : m_pObjects)
	{
		object->Draw();
	}
	for (Enemy* enemy : m_pEnemies)
	{
		enemy->Draw();
	}

}

void Room::Update(float elapsedSec, Isaac* isaac)
{
	m_IsCleared = true;
	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		m_pEnemies[i]->Update(elapsedSec, this, isaac, (int)i);
		if (!m_pEnemies[i]->IsDead())
		{
			m_IsCleared = false;
		}

	}
	if (m_IsCleared)
	{
		OpenDoors();
	}
	for (Door* door : m_pDoors)
	{
		door->Update(elapsedSec);
	}

}

Rectf Room::GetBoundaries() const
{
	return m_Shape;
}

std::vector<GameObject*> Room::GetGameObjects() const
{
	return m_pObjects;
}

std::vector<Enemy*> Room::GetEnemies() const
{
	return m_pEnemies;
}

size_t Room::GetNrObjects() const
{
	return m_pObjects.size();
}

std::vector<Point2f> Room::GetWalkableAreaVertices() const
{
	return m_WalkableAreaVertices;
}

void Room::PlaceDoor(const TextureManager& textureManager, const Point2f& doorCenter, Door::DoorDirection direction)
{
	m_pDoors.push_back(new Door(textureManager, doorCenter, Door::DoorState::closed, direction));

	m_IsCleared ? m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::open) : m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::closed);

}

void Room::OpenDoors()
{
	for (Door* door : m_pDoors)
	{
		door->SetState(Door::DoorState::open);
	}
}

void Room::CloseDoors()
{
	for (Door* door : m_pDoors)
	{
		door->SetState(Door::DoorState::closed);
	}
}
