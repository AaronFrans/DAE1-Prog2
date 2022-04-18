#pragma once
#include <vector>
class GameObject;
class Texture;
class Enemy;
class Isaac;
class Room
{

public:

	Room(Texture* background, Rectf shape, std::vector<GameObject*> objects,
		std::vector<Enemy*> enemies, std::vector<Point2f> walkableAreaVertices);

	Room(const Room& rhs) = default;
	Room(Room && rhs) = default;
	Room& operator=(const Room & rhs) = default;
	Room& operator=(Room && rhs) = default;
	~Room();

	void Draw() const;
	void Update(float elapsedSec, Isaac* isaac);

	Rectf GetBoundaries() const;

	std::vector<GameObject*> GetGameObjects() const;
	std::vector<Enemy*> GetEnemies() const;
	size_t GetNrObjects() const;
	std::vector<Point2f> GetWalkableAreaVertices() const;

private:

	Texture* m_pBackground;
	std::vector<GameObject*> m_pObjects;
	std::vector<Enemy*> m_pEnemies;
	std::vector<Point2f> m_WalkableAreaVertices;
	Rectf m_Shape;



};

