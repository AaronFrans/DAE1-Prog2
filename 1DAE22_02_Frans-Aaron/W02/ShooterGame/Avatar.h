#pragma once
#include "Bullet.h"

class Enemy;

class Avatar
{
public:
	Avatar();
	Avatar(const Point2f& center, float width, float height);

	void Draw() const;
	void Update(float elapsedSec, Enemy* pEnemies, int numEnemies);

	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

private:
	Point2f m_Center;
	float m_Height;
	float m_Width;
	float m_Speed;
	Rectf m_Boundaries;
	Bullet m_Bullet;


	void Clamp();
	void HandleMoveKeysState(float elapsedSec);
};

