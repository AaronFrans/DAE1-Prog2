#pragma once
#include "Vector2f.h"
class Sprite;
class Texture;
class Tear
{

public:
	enum class TearState
	{
		active,
		inactive
	};

	Tear(Texture* texture);
	~Tear();

	void Draw() const;
	void Update(float elapsedSec);

	TearState GetState() const;
	void SetState(TearState state);

	void SetVelocity(Vector2f velocity);

	void SetTearShape(Circlef tearShape);

	void SetHeight(float height);
private:

	Sprite* m_pTearSprite;
	Circlef m_TearShape;
	Vector2f m_Velocity;
	TearState m_State;

	Point2f mTearSpriteLeftBottom;

	float m_Height;
};

