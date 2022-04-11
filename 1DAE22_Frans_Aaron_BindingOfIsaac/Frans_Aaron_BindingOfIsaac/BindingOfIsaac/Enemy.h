#pragma once
#include "Vector2f.h"

class Room;
class Isaac;
class Enemy
{
public:

	Enemy(Point2f centerPoint, float damage, float speed);

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac) = 0;

	virtual bool IsDead() const = 0;

protected:

	bool m_HasDied;

	Point2f m_CenterPosition;
	float m_Damage;

	float m_Speed;
	Vector2f m_Velocity;

	virtual void UpdatePos(float elapsedSec, const Room* currentRoom) = 0;

private:
};

