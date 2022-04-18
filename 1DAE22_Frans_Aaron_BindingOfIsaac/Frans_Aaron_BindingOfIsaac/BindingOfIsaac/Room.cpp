#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "Enemy.h"
#include "GameObject.h"


Room::Room(Texture* background, Rectf shape, std::vector<GameObject*> objects,
	std::vector<Enemy*> enemies, std::vector<Point2f> walkableAreaVertices)
	: m_pBackground{ background }
	, m_Shape{ shape }
	, m_pObjects{ objects }
	, m_WalkableAreaVertices{ walkableAreaVertices }
	, m_pEnemies{ enemies }
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


}

void Room::Draw() const
{
	m_pBackground->Draw(m_Shape);

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
	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		m_pEnemies[i]->Update(elapsedSec, this, isaac, (int)i);
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
