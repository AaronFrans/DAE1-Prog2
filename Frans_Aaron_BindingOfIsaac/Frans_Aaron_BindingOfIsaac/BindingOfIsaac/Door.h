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

	Door(const TextureManager& textureManager, Point2f center, DoorState state, DoorDirection direction, Rectf shape);
	
	Door(const Door& rhs);
	Door(Door && rhs) = default;
	Door& operator=(const Door & rhs);
	Door& operator=(Door && rhs) = default;
	virtual ~Door() = default;

	void Draw() const;
	void Update(float elapsedSec);

	void SetState(DoorState state);
	void Activate();

	DoorDirection GetDirection();

	Rectf GetShape() const;
	bool IsActive() const;


	void SetRoomOrigin(const Point2f& roomOrigin);
	
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

	DoorState m_State;
	DoorDirection m_Direction;

	bool m_IsActive;

	Rectf m_Shape;

	void DrawUp() const;
	void DrawLeft() const;
	void DrawDown() const;
	void DrawRight() const;


	void DrawSprite() const;

};

