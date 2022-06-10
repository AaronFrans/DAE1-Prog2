#pragma once
#include "Vector2f.h"
#include "TextureManager.h"
#include <vector>

class Room;
class Isaac;
class TearManager;
class SoundEffectManager;
class Enemy
{
public:

	Enemy(Point2f centerPoint, float damage, float speed, float health, SoundEffectManager* soundEffectManager);

	Enemy(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy& operator=(Enemy&&) = default;
	virtual ~Enemy() = default;


	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
		const Room* currentRoom, Isaac* isaac, int currentEnemyIndex)  = 0;


	virtual void TakeDamage(float damage) = 0;

	virtual bool IsDead() const = 0;
	virtual Circlef GetHitBox() const = 0;
	
	void SetPosition(const Point2f& center);
	Point2f GetCenter();

	virtual Enemy* Clone() const = 0;

protected:

	SoundEffectManager* m_pSoundEffectManager;
	bool m_HasDied;

	Point2f m_CenterPosition;
	float m_Damage;

	float m_Health;

	float m_Speed;
	Vector2f m_Velocity;

	bool m_PlayedDeathSound;

	float m_Height;

	virtual void DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex) = 0;

	void DoRoomCollision(const Room* currentRoom);
};

