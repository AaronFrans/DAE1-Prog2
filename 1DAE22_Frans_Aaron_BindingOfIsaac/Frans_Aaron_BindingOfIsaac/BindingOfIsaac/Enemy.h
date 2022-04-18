#pragma once
#include "Vector2f.h"
#include <vector>

class Room;
class Isaac;
class Enemy
{
public:

	Enemy(Point2f centerPoint, float damage, float speed, float health);

	Enemy(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy& operator=(Enemy&&) = default;
	virtual ~Enemy() = default;


	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) = 0;


	virtual void TakeDamage(float damage) = 0;

	virtual bool IsDead() const = 0;
	virtual Circlef GetHitBox() const = 0;
	
	void SetPosition(const Point2f& center);

	virtual Enemy* clone() const = 0;

protected:

	bool m_HasDied;

	Point2f m_CenterPosition;
	float m_Damage;

	float m_Health;

	float m_Speed;
	Vector2f m_Velocity;

	void DoEnemyCollisions(const std::vector<Enemy*>& roomEnemies, int currentEnemyIndex);

	void DoRoomCollision(const Room* currentRoom);
};

