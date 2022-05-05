#pragma once
class Texture;
class TextureManager;

class Door
{

public:

	enum class DoorState
	{
		closed,
		closing,
		opening,
		open
	};

	enum class DoorDirection
	{
		up,
		down,
		left,
		right
	};

	Door(const TextureManager& textureManager, Point2f center, DoorState state, DoorDirection direction);
	
	Door(const Door& rhs) = default;
	Door(Door && rhs) = default;
	Door& operator=(const Door & rhs) = default;
	Door& operator=(Door && rhs) = default;
	virtual ~Door() = default;

	void Draw() const;
	void Update(float elapsedSec);

	void SetState(DoorState state);

private:

	Texture* m_pDoorFrame;
	Texture* m_pDoorHallway;
	Texture* m_pDoorRight;
	Texture* m_pDoorLeft;


	Point2f m_Center;

	float m_Width;
	float m_Height;
	float m_HallwayWidth;
	float m_HallwayHeight;

	float m_temp;

	DoorState m_State;
	DoorDirection m_Direction;

	void DrawUp() const;
	void DrawLeft() const;
	void DrawDown() const;
	void DrawRight() const;


	void DrawSprite() const;

};

