#pragma once
#include "Enemy.h"
#include <vector>

class Texture;
class Sprite;
class Room;
class GameObject;
class SmallSpider : public Enemy
{
public:
	enum class SmallSpiderState
	{
		idle,
		moving,
		dying,
		dead
	};

	SmallSpider(Texture* movementSpriteSheet, Texture* deathSpriteSheet, Point2f centerPoint, float damage, float speed);
	~SmallSpider();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac) override;

	virtual bool IsDead() const override;

private:
	Sprite* m_pMovementSprite;
	Sprite* m_pDeathSprite;

	float m_MovementWidth;
	float m_MovementHeight;
	float m_DeathWidth;
	float m_DeathHeight;

	float m_MovementAccuSec;
	float m_MovementMaxSec;

	float m_IdleAccuSec;
	float m_IdleMinSec;

	SmallSpiderState m_State;

	virtual void UpdatePos(float elapsedSec, const Room* currentRoom) override;

	void DoIdle(float elapsedSec);

	void DoRoomCollision(const Room* currentRoom);
	void DoGameObjectCollision(const std::vector<GameObject*>& objects);

	void DoIsaacCollisionCheck(Isaac* isaac);
};

