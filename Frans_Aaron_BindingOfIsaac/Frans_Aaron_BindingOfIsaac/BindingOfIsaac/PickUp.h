#pragma once

class Texture;
class Isaac;
class PickUp final
{

public:

	enum class Type
	{
		fullHeart,
		halfHeart,
	};


	PickUp(Texture* texture, Type type, Point2f centerPos);

	void Draw() const;

	bool HasIsaacCollision(Isaac* isaac);

	Circlef GetShape() const;

private:

	Texture* m_pTexture;

	Type m_Type;
	Point2f m_CenterPos;

	float m_ShapeSize;


	float m_DrawWidth;
	float m_DrawHeight;
};

