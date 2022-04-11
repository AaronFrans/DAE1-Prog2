#pragma once
#include "Vector2f.h"
#include <vector>
//TODO: 17. think about shadow
//TODO: 18. relook at up/ diagonal/ down tear drop

class Sprite;
class Texture;
class GameObject;
class Tear final
{

public:
	enum class TearState
	{
		active,
		groundHit,
		inactive
	};

	Tear();
	~Tear();

	void Draw() const;
	void Update(float elapsedSec, std::vector<GameObject*> gameObjects);

	TearState GetState() const;
	bool GetIsFront() const;

	void SetState(TearState state);
	void SetVelocity(Vector2f velocity);
	void SetTearShape(Point2f center, float tearRadius);
	void SetHeight(float height);
	void SetTearTexture(Texture* tearTexture);
	void SetTearHitSprite(Texture* tearHitTexture);
	void SetRange(float range);
	void SetIsFront(bool isFront);

private:

	Texture* m_pTearTexture;
	Sprite* m_pTearHitSprite;
	Point2f m_Center;
	float m_TearRadius;
	Vector2f m_Velocity;
	TearState m_State;

	Point2f mTearSpriteLeftBottom;

	float m_Height;
	float m_HeightDecrease;

	float m_TotalGroundTime;
	float m_AccuGroundTime;

	bool m_IsFront;

	Rectf m_TearRange;

	void ClearTear();
};

