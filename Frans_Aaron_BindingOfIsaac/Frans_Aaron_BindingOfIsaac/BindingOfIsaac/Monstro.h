#pragma once
#include "Boss.h"

class Texture;
class Sprite;
class Monstro final : public Boss
{
public:

	enum class MonstroState
	{
		idle,
		charginSpit,
		attackSpit,
		jumpHighStart,
		jumpHighUp,
		jumpHighDown,
		jumpHighEnd,
		jumpSmallStart,
		jumpSmallUp,
		jumpSmallDown,
		jumpSmallEnd,
		dying,
		dead,
	};

	enum class Direction
	{
		left,
		right
	};

	Monstro(Texture* spriteSheet, Texture* shadow, Texture* healthBarTexture,
		Texture* deathBloodSheet, Point2f centerPoint, SoundEffectManager* soundEffectManager);

	Monstro(const Monstro& rhs);
	Monstro(Monstro&& rhs) = default;
	Monstro& operator=(const Monstro& rhs);
	Monstro& operator=(Monstro&& rhs) = default;
	~Monstro();


	virtual void Draw() const override;
	virtual void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager,
		const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) override;


	virtual void TakeDamage(float damage) override;

	virtual bool IsDead() const override;
	virtual Circlef GetHitBox() const override;


	virtual Enemy* Clone() const override;

private:

	MonstroState m_State;
	Direction m_Direction;

	Texture* m_pSpriteSheet;
	Texture* m_pShadow;
	Sprite* m_pDeathBlood;

	float m_SrcWidth;
	float m_SrcHeight;
	float m_ShapeRadius;

	float m_IdleAccuTime;
	float m_IdleMinTime;

	float m_SpitChargeAccuTime;
	float m_SpitChargeMinTime;

	float m_SpitAttackAccuTime;
	float m_SpitAttackDurTime;

	float m_JumpAttackHighChargeAccuTime;
	float m_JumpAttackHighChargeDurTime;

	float m_JumpAttackHighFloatAccuTime;
	float m_JumpAttackHighFloatMinTime;

	float m_JumpAttackHighLandAccuTime;
	float m_JumpAttackHighLandDurTime;

	float m_JumpAttackLowChargeAccuTime;
	float m_JumpAttackLowChargeDurTime;

	float m_JumpAttackLowLandAccuTime;
	float m_JumpAttackLowLandDurTime;

	float m_NewDeathSplatterSfxAccuTime;
	float m_NewDeathSplatterSfxMinTime;

	float m_DyingAccuTime;
	float m_DyingDurTime;

	float m_JumpHighSpeed;

	float m_JumpSmallSpeed;
	float m_JumpSmallMaxHeight;

	Point2f m_SmallJumpTarget;
	float m_SpitNrShots;

	float m_MinShotSpeed;
	float m_MaxShotSpeed;

	int m_MinTearHeight;
	int m_MaxTearHeight;

	float m_TearRange;

	bool m_OfScreen;
	bool m_HasShotTears;

	bool m_PlayedCurrentStateSfx;

	void ChangeState(float elapsedSec);

	void UpdatePos(float elapsedSec, Isaac* isaac);
	void UpdateDirection(Isaac* isaac);

	virtual void DoEnemyCollisions(const std::vector<Enemy*>& roomEnemies, int currentEnemyIndex) override;

	void ShootBullets(Isaac* isaac, TearManager* tearManager, const TextureManager& textureManager);

	void Shoot(TearManager* tearManager, const TextureManager& textureManager, Vector2f tearVelocity);

	void DoIsaacCollisionCheck(Isaac* isaac);
};

