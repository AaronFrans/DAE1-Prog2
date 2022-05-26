#pragma once
#include "Enemy.h"
class Boss : public Enemy
{

public:

	Boss(Point2f centerPoint, float damage, float speed, float health);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Room* currentRoom, Isaac* isaac, int currentEnemyIndex) override;


	virtual void TakeDamage(float damage) override;

	virtual bool IsDead() const override;
	virtual Circlef GetHitBox() const override;


	virtual Enemy* Clone() const override;
private:


};

