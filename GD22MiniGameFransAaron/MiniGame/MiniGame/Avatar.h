#pragma once
#include "Vector2f.h"

class Level;
class Texture;

class Avatar
{
	enum class ActionState
	{
		waiting = 0,
		moving = 1,
		transforming = 2

	};

public:

	Avatar();
	~Avatar();

	void Update(float elapsedSec, const Level& level);
	void Draw() const;

	void PowerUpHit();

	Rectf GetShape();

private:
	Texture* m_pSpritesTexture;

	float m_ClipHeight;
	float m_ClipWidth;
	float m_AnimTime;
	int m_NrOfFrames;
	int m_NrOfFramesPerSec;
	int m_AnimFrame;

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

	void UpdateCurrentFrame(float elapsedSec);
};

