#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>
class Sprite;
class TextureManager;
class TearManager;
class Room;
class GameObject;
class IsaacHealthBar;

//TODO: 0. 1-13 before vaction over
//TODO: 17. make function for fire rate

class Isaac final
{

	enum class Direction
	{
		up = 1,
		down = 2,
		left = 3,
		right = 4
	};

	enum class HeadState
	{
		idle = 1,
		shooting = 2
	};

	enum class BodyState
	{
		idle = 1,
		walking = 2
	};

	enum class DamageState
	{
		undamaged,
		hurt,
		dead
	};

public:

	Isaac(const TextureManager& textureManager, IsaacHealthBar* isaacHealthBar, const Point2f& centerPosition);

	Isaac(const Isaac& rhs) = default;
	Isaac(Isaac && rhs) = default;
	Isaac& operator=(const Isaac & rhs) = default;
	Isaac& operator=(Isaac && rhs) = default;
	~Isaac();

	void Draw() const;
	void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager, Room* currentRoom);

	void TakeDamage(float damage);

	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	Point2f GetCenter() const;
	Rectf GetHitBox() const;

private:

	const float m_MaxIdleTime{ 1 };

	Sprite* m_pHeadSprite;
	Sprite* m_pWalkSpriteUD;
	Sprite* m_pWalkSpriteLR;
	Sprite* m_pHurtSprite;
	IsaacHealthBar* m_pHealth;

	Point2f m_CenterPosition;
	float m_Width;
	float m_Height;

	Point2f m_TearSrcBottomLeft;

	Direction m_BodyDirection;
	Direction m_HeadDirection;

	BodyState m_BodyState;
	HeadState m_HeadState;

	DamageState m_DamageState;

	float m_TearFireRate;
	float m_TearFireAccuSec;
	float m_IdleAccuSec;

	float m_InvisAccuSec;
	float m_InvisMaxSec;

	Vector2f m_Velocity;

	//Character Changeable Stats
	float m_WalkSpeed;
	float m_TearHeight;
	float m_TearSpeed;
	float m_TearRange;
	float m_Damage;



	void DrawBody() const;
	void UpdateBody(float elapsedSec);
	void UpdatePos(float elapsedSec, Room* currentRoom);

	void DoRoomCollision(const Room* currentRoom);
	void DoGameObjectCollision(const std::vector<GameObject*>& objects);

	void DrawHead() const;
	void UpdateHead(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager);

	void Shoot(TearManager* tearManager, const TextureManager& textureManager, Vector2f tearVelocity);


	void DrawHurt() const;
	void UpdateHurt(float elapsedSec);

	void DrawDead() const;
	void UpdateDead(float elapsedSec);

	bool CanShoot();
	bool IsInvis();

};

