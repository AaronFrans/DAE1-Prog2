#pragma once
#include "Enemy.h"

class Texture;
class Sprite;
class Room;
class Fly final : public Enemy
{

public:

	enum class FlyState
	{
		moving,
		dying,
		dead
	};


	Fly(Texture* movementSpriteSheet, Texture* DyingSpriteSheet, Point2f centerPoint, SoundEffectManager* soundEffectManager);

	Fly(const Fly& rhs);
	Fly(Fly&& rhs) = default;
	Fly& operator=(const Fly& rhs);
	Fly& operator=(Fly&& rhs) = default;
	~Fly();

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

	float m_DyingAccuSec;
	float m_DyingMaxSec;

	bool m_FlyingSoundPlaying;

	float m_FlyingSoundDur;
	float m_FlyingSoundAccuSec;

	FlyState m_State;

	void UpdatePos(float elapsedSec, const Room* currentRoom, Isaac* isaac);

	void DoIsaacCollisionCheck(Isaac* isaac);
	virtual void DoEnemyCollisions(const std::vector<Enemy*>& enemies, int currentEnemyIndex) override;

	void DoDying(float elapsedSec);
};

