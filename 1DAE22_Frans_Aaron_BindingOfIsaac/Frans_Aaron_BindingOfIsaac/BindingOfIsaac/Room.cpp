#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "GameObject.h"


Room::Room(Texture* background, Rectf shape, std::vector<GameObject*> objects, std::vector<Point2f> walkableAreaVertices)
	: m_pBackground{ background }
	, m_Shape{ shape }
	, m_pObjects{ objects }
	, m_WalkableAreaVertices{ walkableAreaVertices }
{
}

Room::~Room()
{
	for (GameObject* object : m_pObjects)
	{
		delete object;
	}
}

void Room::Draw() const
{
	m_pBackground->Draw(m_Shape);

	for (GameObject* object : m_pObjects)
	{
		object->Draw();
	}

}

void Room::Update()
{
}

Rectf Room::GetBoundaries() const
{
	return m_Shape;
}

std::vector<GameObject*> Room::GetGameObjects() const
{
	return m_pObjects;
}

size_t Room::GetNrObjects() const
{
	return m_pObjects.size();
}

std::vector<Point2f> Room::GetWalkableAreaVertices() const
{
	return m_WalkableAreaVertices;
}