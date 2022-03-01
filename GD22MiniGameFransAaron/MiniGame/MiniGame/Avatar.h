#pragma once
#include "Vector2f.h"

class Level;

class Avatar
{
	enum class ActionState
	{
		waiting,
		moving,
		transforming

	};

public:

	Avatar();

	void Update(float elapsedSec, const Level& level);
	void Draw() const;

	void PowerUpHit();

	Rectf GetShape();

private:
	const float m_HorSpeed;
	const float m_JumpSpeed;
	const Vector2f m_Acceleration;


	Vector2f m_Velocity;
	Rectf m_Shape;
	ActionState m_ActionState;

	float m_AccuTransformSec;
	const float m_MaxTransformSec;
	int m_Power;

	void UpdatePos(float elapsedSec, bool isOnGround, const Level& level);
	void HandleCollision(const Level& level);

};

