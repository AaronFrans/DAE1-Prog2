#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemPedestal.h"
#include "TearManager.h"
#include "Boss.h"
#include "SoundEffect.h"


Room::Room(Texture* background, SoundEffect* doorOpenSound, SoundEffect* doorCloseSound, Rectf shape, std::vector<GameObject*> objects,
	std::vector<std::vector<Point2f>> enemyGroupPositions, std::vector<Point2f> walkableAreaVertices,
	RoomType type)
	: m_pBackground{ background }
	, m_Shape{ shape }
	, m_pObjects{ objects }
	, m_WalkableAreaVertices{ walkableAreaVertices }
	, m_EnemyGroupPositions{ enemyGroupPositions }
	, m_Type{ type }
	, m_pDoorOpenSound{ doorOpenSound }
	, m_pDoorCloseSound{ doorCloseSound }
{
}

Room::Room(const Room& rhs)
	: m_pBackground{ rhs.m_pBackground }
	, m_Shape{ rhs.m_Shape }
	, m_WalkableAreaVertices{ rhs.m_WalkableAreaVertices }
	, m_Type{ rhs.m_Type }
	, m_EnemyGroupPositions{ rhs.m_EnemyGroupPositions }
	, m_pDoorOpenSound{ rhs.m_pDoorOpenSound }
	, m_pDoorCloseSound{ rhs.m_pDoorCloseSound }
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
	for (ItemPedestal* pedestal : rhs.m_pPedestals)
	{
		m_pPedestals.push_back(new ItemPedestal(*pedestal));
	}
}

Room& Room::operator=(const Room& rhs)
{
	m_pBackground = rhs.m_pBackground;
	m_Shape = rhs.m_Shape;
	m_WalkableAreaVertices = rhs.m_WalkableAreaVertices;
	m_Type = rhs.m_Type;
	m_pDoorOpenSound = rhs.m_pDoorOpenSound;
	m_pDoorCloseSound = rhs.m_pDoorCloseSound;

	m_EnemyGroupPositions = rhs.m_EnemyGroupPositions;

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
	for (ItemPedestal* pedestal : rhs.m_pPedestals)
	{
		m_pPedestals.push_back(new ItemPedestal(*pedestal));
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
	for (ItemPedestal* itemPedestal : m_pPedestals)
	{
		delete itemPedestal;
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
	for (ItemPedestal* itemPedestal : m_pPedestals)
	{
		itemPedestal->Draw();;
	}

}

void Room::Update(float elapsedSec, Isaac* isaac, TearManager* tearManager, const TextureManager& textureManager)
{

	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		m_pEnemies[i]->Update(elapsedSec, tearManager, textureManager, this, isaac, (int)i);
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
		vertex.x += origin.x;
		vertex.y += origin.y;
	}
}

void Room::PlaceDoor(const TextureManager& textureManager, const Point2f& doorCenter, Door::DoorDirection direction, Rectf shape)
{
	Door::DoorType roomType{ int(m_Type) };

	m_pDoors.push_back(new Door(textureManager, doorCenter, Door::DoorState::closed, direction, shape, roomType));

	IsCleared() ? m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::open) : m_pDoors[m_pDoors.size() - 1]->SetState(Door::DoorState::closed);

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

void Room::InitEnemies( EnemyManager* enemyManager)
{
	Enemy* pRandomEnemy = nullptr;
	Enemy* pEnemy = pRandomEnemy;
	Circlef enemyShape = Circlef{};
	if (m_Type == RoomType::normal)
	{
		for (std::vector<Point2f> group : m_EnemyGroupPositions)
		{
			pRandomEnemy = enemyManager->GetRandomEnemy(EnemyManager::Floor::basement);
			pEnemy = pRandomEnemy;

			for (Point2f enemyPos : group)
			{
				pEnemy->SetPosition(enemyPos);
				m_pEnemies.push_back(pEnemy->Clone());
			}
		}
	}
	else if (m_Type == RoomType::boss)
	{
		for (std::vector<Point2f> group : m_EnemyGroupPositions)
		{
			pRandomEnemy = enemyManager->GetRandomBoss(EnemyManager::Floor::basement);
			pEnemy = pRandomEnemy;

			for (Point2f enemyPos : group)
			{
				pEnemy->SetPosition(enemyPos);
				m_pEnemies.push_back(pEnemy->Clone());
			}
		}
	}



}

void Room::ChangeDoorType(Door::DoorDirection direction, Door::DoorType type,
	const TextureManager& textureManager)
{
	for (Door* door : m_pDoors)
	{
		if (door->GetDirection() == direction)
			door->ChangeDoorType(type, textureManager);

	}
}

void Room::AddPedestal(Item* item, Texture* pedestalTexture)
{
	ItemPedestal* pedestal{ new ItemPedestal{pedestalTexture, Point2f{m_Shape.width / 2.0f, m_Shape.height / 2.0f }, 30} };

	pedestal->PlaceItem(item);

	m_pPedestals.push_back(pedestal);
}

std::vector<Door*> Room::GetDoors()
{
	return m_pDoors;
}

Rectf Room::GetDoorShape(Door::DoorDirection direction)
{

	for (Door* door : m_pDoors)
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
	bool isCleared{ true };
	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		if (!m_pEnemies[i]->IsDead())
		{
			isCleared = false;
		}

	}
	return isCleared;
}

bool Room::AreDoorsOpen() const
{
	bool areDoorsOpen{ false };
	for (Door* door : m_pDoors)
	{
		if (areDoorsOpen == false && door->GetState() == Door::DoorState::open)
		{
			areDoorsOpen = true;
		}
	}
	return areDoorsOpen;
}

Room::RoomType Room::GetType() const
{
	return m_Type;
}

std::vector<ItemPedestal*> Room::GetPedestals()
{
	return m_pPedestals;
}

BossHealthBar* Room::GetBossHealthBar()
{
	if (m_Type == RoomType::boss)
	{
		Boss* boss{ static_cast<Boss*> (m_pEnemies[0]) };
		return boss->GetHealthBar();
	}
	return nullptr;
}


void Room::OpenDoors()
{
	m_pDoorOpenSound->SetVolume(20);
	m_pDoorOpenSound->Play(false);
	for (Door* door : m_pDoors)
	{
		door->SetState(Door::DoorState::open);
	}
}

void Room::CloseDoors()
{
	m_pDoorCloseSound->SetVolume(20);
	m_pDoorCloseSound->Play(false);
	for (Door* door : m_pDoors)
	{
		door->SetState(Door::DoorState::closed);
	}
}
