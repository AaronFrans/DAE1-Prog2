#pragma once
#include "Vector2f.h"

class Enemy;

class Bullet
{

public:

	Bullet();
	Bullet(float width, float height);

	void Draw() const;
	void Update(float elapsedSec, Enemy* pEnemies, int numEnemies);
	void Shoot(const Point2f& center, const Vector2f& velocity);
	
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);

private:

	Point2f m_Center;
	float m_Width;
	float m_Height;
	Vector2f m_Velocity;
	Rectf m_Boundaries;
	bool m_IsActivated;

	void CheckBoundaries();
	void CheckEnemiesHit(Enemy* pEnemies, int numEnemies);

};

