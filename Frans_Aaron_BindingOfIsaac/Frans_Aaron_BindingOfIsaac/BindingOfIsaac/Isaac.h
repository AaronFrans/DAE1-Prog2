#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>

class Texture;
class Sprite;
class TextureManager;
class TearManager;
class Room;
class GameObject;
class IsaacHealthBar;
class ItemPedestal;
class Costume;
class ItemManager;
class Item;
class SoundEffectManager;

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



public:

	enum class DamageState
	{
		undamaged,
		hurt,
		dying,
		dead
	};

	Isaac(const TextureManager& textureManager, SoundEffectManager* soundEffectManager,
		IsaacHealthBar* isaacHealthBar, const Point2f& centerPosition);

	Isaac(const Isaac& rhs) = default;
	Isaac(Isaac&& rhs) = default;
	Isaac& operator=(const Isaac& rhs) = default;
	Isaac& operator=(Isaac&& rhs) = default;
	~Isaac();

	void Draw() const;
	void Update(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager, Room* currentRoom, ItemManager* itemManager);

	void TakeDamage(float damage);

	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	Point2f GetCenter() const;
	void SetCenter(const Point2f& center);

	Circlef GetHitBox() const;

	DamageState GetDamageState();
	bool IsFullHealth();

	void Heal(float healAmount);

private:

	const float m_MaxIdleTime{ 1 };

	SoundEffectManager* m_pSoundEffectManager;

	Sprite* m_pHeadSprite;
	Sprite* m_pWalkSpriteUD;
	Sprite* m_pWalkSpriteLR;
	Sprite* m_pHurtSprite;
	Sprite* m_pDyingSprite;
	Texture* m_Shadow;

	Point2f m_CenterPosition;
	float m_MovementWidth;
	float m_MovementHeight;

	float m_DyingWidth;
	float m_DyingHeight;

	Point2f m_TearSrcBottomLeft;

	Direction m_BodyDirection;
	Direction m_HeadDirection;

	BodyState m_BodyState;
	HeadState m_HeadState;

	DamageState m_DamageState;

	float m_TearFireAccuSec;
	float m_IdleAccuSec;

	float m_InvisAccuSec;
	float m_InvisMaxSec;

	Vector2f m_Velocity;

	float m_DeathRotationAngle;

	std::vector<Costume*> m_pCostumes;

	bool m_EvenShot;


	//Character Changeable Stats
	float m_WalkSpeed;
	float m_TearHeight;
	float m_TearSpeed;
	float m_TearRange;
	float m_Damage;
	float m_TearFireRate;
	IsaacHealthBar* m_pHealth;


	void DrawBody() const;
	void DrawBodyCostumes() const;
	void UpdateBody(float elapsedSec);
	void UpdatePos(float elapsedSec, Room* currentRoom, ItemManager* itemManager);


	void DoRoomCollision(const Room* currentRoom);
	void DoGameObjectCollision(const std::vector<GameObject*>& objects, const std::vector<ItemPedestal*>& pedestals, ItemManager* itemManager);

	void DrawHead() const;
	void DrawHeadCostumes() const;
	void UpdateHead(float elapsedSec, TearManager* tearManager, const TextureManager& textureManager);

	void Shoot(TearManager* tearManager, const TextureManager& textureManager, Vector2f tearVelocity);


	void DrawHurt() const;
	void UpdateHurt(float elapsedSec);

	void DrawDying() const;
	void UpdateDying(float elapsedSec);

	bool CanShoot();
	bool IsInvis();

	void PickUpItem(Item* item, ItemManager* itemManager);
};

