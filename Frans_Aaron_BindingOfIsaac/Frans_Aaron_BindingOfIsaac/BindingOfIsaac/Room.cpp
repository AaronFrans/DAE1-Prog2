#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "Enemy.h"
#include "GameObject.h"


Room::Room(Texture* background, Rectf shape, std::vector<GameObject*> objects,
	std::vector<std::vector<Point2f>> enemyGroupPositions, std::vector<Point2f> walkableAreaVertices,
	RoomType type, bool isCleared)
	: m_pBackground{ background }
	, m_Shape{ shape }
	, m_pObjects{ objects }
	, m_WalkableAreaVertices{ walkableAreaVertices }
	, m_EnemyGroupPositions{enemyGroupPositions}
	, m_Type{ type }
	, m_IsCleared{ isCleared }
{
}

Room::Room(const Room& rhs)
	: m_pBackground{ rhs.m_pBackground }
	, m_Shape{ rhs.m_Shape }
	, m_WalkableAreaVertices{ rhs.m_WalkableAreaVertices }
	, m_Type{ rhs.m_Type }
	, m_IsCleared{ rhs.m_IsCleared }
{
	for (Enemy* enemy : rhs.m_pEnemies)
	{
		m_pEnemies.push_back(enemy->Clone());
	}
	for (GameObject* object : rhs.m_pObjects)
	{
		m_pObjects.push_back(object->Clone());
	}
	for (Door* door : rhs.m_pDoors)
	{
		m_pDoors.push_back(new Door(*door));
	}
}

Room& Room::operator=(const Room& rhs)
{
	m_pBackground = rhs.m_pBackground;
	m_Shape = rhs.m_Shape;
	m_WalkableAreaVertices = rhs.m_WalkableAreaVertices;
	m_Type = rhs.m_Type;
	m_IsCleared = rhs.m_IsCleared;


	for (Enemy* enemy : rhs.m_pEnemies)
	{
		m_pEnemies.push_back(enemy);
	}
	for (GameObject* object : rhs.m_pObjects)
	{
		m_pObjects.push_back(object);
	}
	for (Door* door : rhs.m_pDoors)
	{
		m_pDoors.push_back(door);
	}

	return *this;
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

void Room::SetOrigin(Point2f origin)
{
	m_Shape.left = origin.x;
	m_Shape.bottom = origin.y;

	for (Door* door : m_pDoors)
	{
		door->SetRoomOrigin(origin);
	}

	for (Point2f& vertex : m_WalkableAreaVertices)
	{
		vertex.x +=  origin.x;
		vertex.y +=  origin.y;
	}
}

void Room::PlaceDoor(const TextureManager& textureManager, const Point2f& doorCenter, Door::DoorDirection direction, Rectf shape)
{
	m_pDoors.push_back(new Door(textureManager, doorCenter, Door::DoorState::closed, direction, shape));

	m_IsCleared ? m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::open) : m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::closed);

}

void Room::ActivateDoor(Door::DoorDirection direction)
{
	for (Door* door : m_pDoors)
	{
		if (door->GetDirection() == direction)
		{
			door->Activate();
		}
	}
}

void Room::InitEnemies(const EnemyManager& enemyManager)
{
	Enemy* pRandomEnemy = nullptr;
	Enemy* pEnemy = pRandomEnemy;
	Circlef enemyShape = Circlef{};

	for (std::vector<Point2f> group : m_EnemyGroupPositions)
	{
		pRandomEnemy = enemyManager.GetRandomEnemy(EnemyManager::Floor::basement);
		pEnemy = pRandomEnemy;
		enemyShape = pEnemy->GetHitBox();

		for (Point2f enemyPos : group)
		{
			pEnemy->SetPosition(enemyPos);
			m_pEnemies.push_back(pEnemy->Clone());
		}
	}

}

std::vector<Door*> Room::GetDoors()
{
	return m_pDoors;
}

Rectf Room::GetDoorShape(Door::DoorDirection direction)
{

	for (Door* door: m_pDoors)
	{
		if (door->GetDirection() == direction)
		{
			return door->GetShape();
		}
	}

	return Rectf{};
}

bool Room::IsCleared() const
{
	return m_IsCleared;
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
