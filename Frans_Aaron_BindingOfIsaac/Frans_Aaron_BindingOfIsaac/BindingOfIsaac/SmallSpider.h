#pragma once
#include "Enemy.h"

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

	SmallSpider(Texture* movementSpriteSheet, Texture* DyingSpriteSheet, Point2f centerPoint, SoundEffectManager* soundEffectManager);

	SmallSpider(const SmallSpider& rhs);
	SmallSpider(SmallSpider&& rhs) = default;
	SmallSpider& operator=(const SmallSpider& rhs);
	SmallSpider& operator=(SmallSpider&& rhs) = default;
	~SmallSpider();



	virtual void Draw() const override;
	virtual void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
		const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) override;

	virtual bool IsDead() const override;
	virtual Circlef GetHitBox() const override;

	virtual void TakeDamage(float damage) override;

	virtual Enemy* Clone() const override;

private:

	Sprite* m_pMovementSprite;
	Sprite* m_pDyingSprite;

	float m_MovementWidth;
	float m_MovementHeight;
	float m_DyingWidth;
	float m_DyingHeight;

	float m_MovementAccuSec;
	float m_MovementMaxSec;

	float m_DyingAccuSec;
	float m_DyingMaxSec;

	float m_IdleAccuSec;
	float m_IdleMinSec;



	SmallSpiderState m_State;

	void UpdatePos(float elapsedSec, const Room* currentRoom);

	void DoIdle(float elapsedSec);

	void DoGameObjectCollision(const std::vector<GameObject*>& objects);
	virtual void DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex) override;

	void DoIsaacCollisionCheck(Isaac* isaac);

	void DoDying(float elapsedSec);
};

