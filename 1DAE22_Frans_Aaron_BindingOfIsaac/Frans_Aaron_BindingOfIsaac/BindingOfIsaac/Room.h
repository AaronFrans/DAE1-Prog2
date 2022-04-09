#pragma once
#include <vector>
class GameObject;
class Texture;

class Room
{

public:

	Room(Texture* background, Rectf shape, std::vector<GameObject*> objects, std::vector<Point2f> walkableAreaVertices);
	~Room();

	void Draw() const;
	void Update();

	Rectf GetBoundaries() const;

	std::vector<GameObject*> GetGameObjects() const;
	size_t GetNrObjects() const;
	std::vector<Point2f> GetWalkableAreaVertices() const;

private:

	Texture* m_pBackground;
	std::vector<GameObject*> m_pObjects;
	std::vector<Point2f> m_WalkableAreaVertices;
	Rectf m_Shape;



};

