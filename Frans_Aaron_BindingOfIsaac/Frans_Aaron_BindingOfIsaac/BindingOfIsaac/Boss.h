#pragma once
#include "Enemy.h"
#include "UIManager.h"

class Boss : public Enemy
{

public:

	enum class DeathState
	{
		alive,
		death
	};

	Boss(Point2f centerPoint, float damage, float speed, float health, Texture* healthBarTexture, SoundEffectManager* soundEffectManager);
	Boss(Point2f centerPoint, float damage, float speed, float health, BossHealthBar* healthBar, SoundEffectManager* soundEffectManager);

	Boss(const Boss& rhs) = default;
	Boss(Boss && rhs) = default;
	Boss& operator=(const Boss & rhs) = default;
	Boss& operator=(Boss && rhs) = default;
	virtual ~Boss();


	virtual void Draw() const override = 0;
	virtual void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
	const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) = 0;


	virtual void TakeDamage(float damage) override = 0;

	virtual bool IsDead() const override = 0;
	virtual Circlef GetHitBox() const override = 0;

	BossHealthBar* GetHealthBar();
	DeathState GetDeathState();

	virtual Enemy* Clone() const override = 0;

protected:

	BossHealthBar* m_pHealthBar;

	DeathState m_DeathState;

};

