#pragma once

class Sprite;
class Costume
{

public:

	enum class CostumeType
	{
		head,
		body
	};

	enum class CostumeDirection
	{
		up,
		down,
		left,
		right
	};

	Costume(Sprite* costumeUD, Sprite* costumeLR,
		Point2f center, Costume::CostumeType type);

	Costume(const Costume& rhs) = default;
	Costume(Costume && rhs) = default;
	Costume& operator=(const Costume & rhs) = default;
	Costume& operator=(Costume && rhs) = default;
	~Costume();


	void Draw() const;
	void Update(float elapsedSec);
	void UpdatePos(float elapsedSec, float moveSpeed);

	void SetPosition(Point2f newPos);
	void SetDirection(CostumeDirection direction);


	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	CostumeType GetType();

private:

	Sprite* m_pCostumeUD;
	Sprite* m_pCostumeLR;

	Point2f m_CenterPosition;

	CostumeDirection m_Direction;
	CostumeType m_Type;

	float m_WidthUD;
	float m_HeightUD;

	float m_WidthLR;
	float m_HeightLR;
};

