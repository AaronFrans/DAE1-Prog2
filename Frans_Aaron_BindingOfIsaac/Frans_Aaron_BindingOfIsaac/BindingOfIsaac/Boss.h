#pragma once
#include "Enemy.h"

class Boss : public Enemy
{

public:

	Boss(Point2f centerPoint, float damage, float speed, float health);

	virtual void Draw() const override = 0;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) override = 0;


	virtual void TakeDamage(float damage) override = 0;

	virtual bool IsDead() const override = 0;
	virtual Circlef GetHitBox() const override = 0;


	virtual Enemy* Clone() const override = 0;

private:


};

