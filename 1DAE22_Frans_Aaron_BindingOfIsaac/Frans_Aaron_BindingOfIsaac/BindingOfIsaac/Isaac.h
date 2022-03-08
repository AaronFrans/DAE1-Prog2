#pragma once
#include "Vector2f.h"
class Sprite;
class TextureManager;
class TearManager;

class Isaac
{

	enum class Direction
	{
		up = 1,
		down = 2,
		left = 3,
		right = 4
	};

public:

	Isaac(const TextureManager& textureManager);
	Isaac(const TextureManager& textureManager, const Point2f& centerPosition);
	~Isaac();

	void Draw() const;

	void Update(float elapsedSec, TearManager* tearManager);

	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	//void SetState(BodyState bodyState);

private:

	Sprite* m_pHeadSprite;
	Sprite* m_pWalkSpriteUD;
	Sprite* m_pWalkSpriteLR;

	Point2f m_CenterPosition;
	Vector2f m_Velocity;

	Direction m_BodyState;
	Direction m_HeadState;

	float m_TearFireRate;
	float m_TearFireAccuSec;

	void DrawBody() const;
	void UpdateBody(float elapsedSec);

	void DrawHead() const;
	void UpdateHead(float elapsedSec, TearManager* tearManager);

	void Shoot(TearManager* tearManager);

	bool CanShoot();
};

