#pragma once
#include "Vector2f.h"
#include <vector>

class Sprite;
class Texture;
class GameObject;
class Enemy;
class ItemPedestal;
class Tear final
{

public:
	enum class TearState
	{
		active,
		hit,
		inactive
	};

	Tear();

	Tear(const Tear& rhs) = default;
	Tear(Tear && rhs) = default;
	Tear& operator=(const Tear & rhs) = default;
	Tear& operator=(Tear && rhs) = default;
	~Tear();


	void Draw() const;
	void Update(float elapsedSec, std::vector<GameObject*> gameObjects, std::vector<Enemy*> enemies, std::vector<ItemPedestal*> pedestals);

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
	void SetDamage(float damage);

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

	float m_Damage;

	bool m_IsFront;

	Rectf m_TearRange;

	void ClearTear();
};

