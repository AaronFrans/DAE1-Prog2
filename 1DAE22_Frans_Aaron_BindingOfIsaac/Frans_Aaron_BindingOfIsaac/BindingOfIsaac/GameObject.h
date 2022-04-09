#pragma once
class Sprite;
class Texture;
class GameObject
{
public:
	GameObject(Texture* objectTexture, int nrColls, int nrRows, Point2f center, float size);
	virtual ~GameObject();

	virtual void Draw() const = 0;
	virtual Rectf GetShape() const;

	virtual bool IsNotDestroyed() const = 0;

protected:

	Sprite* m_pSprite;
	Rectf m_Shape;
	Point2f m_Center;
};

