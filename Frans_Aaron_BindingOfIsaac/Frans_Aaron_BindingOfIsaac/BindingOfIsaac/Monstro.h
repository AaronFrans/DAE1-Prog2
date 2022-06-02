#pragma once
#include "Boss.h"

class Texture;
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

	Monstro(Texture* spriteSheet, Point2f centerPoint, float damage, float speed, float health);



	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) override;


	virtual void TakeDamage(float damage) override;

	virtual bool IsDead() const override;
	virtual Circlef GetHitBox() const override;


	virtual Enemy* Clone() const override;

private:

	MonstroState m_State;

	Texture* m_SpriteSheet;

	float m_SrcWidth;
	float m_SrcHeight;

	float m_Height;

	float m_IdleAccuTime;
	const float m_IdleMinTime;

	float m_SpitChargeAccuTime;
	const float m_SpitChargeMinTime;

	float m_SpitAttackAccuTime;
	const float m_SpitAttackDurTime;

	float m_JumpAttackHighChargeAccuTime;
	const float m_JumpAttackHighChargeDurTime;

	float m_JumpAttackHighFloatAccuTime;
	const float m_JumpAttackHighFloatMinTime;

	float m_JumpAttackHighLandAccuTime;
	const float m_JumpAttackHighLandDurTime;

	float m_JumpAttackLowChargeAccuTime;
	const float m_JumpAttackLowChargeDurTime;

	float m_JumpAttackLowLandAccuTime;
	const float m_JumpAttackLowLandDurTime;

	const float m_JumpHighSpeed;

	const float m_JumpSmallSpeed;
	const float m_JumpSmallMaxHeight;

	bool m_OfScreen;

	void ChangeState(float elapsedSec);

	virtual void DoEnemyCollisions(const std::vector<Enemy*>& roomEnemies, int currentEnemyIndex) override;

};

