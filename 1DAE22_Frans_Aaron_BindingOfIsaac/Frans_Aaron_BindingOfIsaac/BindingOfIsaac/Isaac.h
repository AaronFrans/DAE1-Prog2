#pragma once
#include "Vector2f.h"
class Sprite;

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

	Isaac();
	Isaac(const Point2f& centerPosition);
	~Isaac();

	void Draw() const;

	void Update(float elapsedSec);

	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	//void SetState(BodyState bodyState);

private:

	static Sprite* m_pHeadSprite;
	static Sprite* m_pWalkSpriteUD;
	static Sprite* m_pWalkSpriteLR;

	Point2f m_CenterPosition;
	Vector2f m_Velocity;

	Direction m_BodyState;
	Direction m_HeadState;

	void DrawBody() const;
	void UpdateBody(float elapsedSec);

	void DrawHead() const;
	void UpdateHead(float elapsedSec);
};

