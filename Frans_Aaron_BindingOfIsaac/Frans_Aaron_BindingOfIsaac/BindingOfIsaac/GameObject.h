#pragma once
class Sprite;
class Texture;
class GameObject
{
public:
	GameObject(Texture* objectTexture, int nrColls, int nrRows, Point2f center, float size);

	GameObject(const GameObject& rhs) = default;
	GameObject(GameObject && rhs) = default;
	GameObject& operator=(const GameObject & rhs) = default;
	GameObject& operator=(GameObject && rhs) = default;
	virtual ~GameObject();

	virtual void Draw() const = 0;
	virtual bool IsNotDestroyed() const = 0;

	Circlef GetShape() const;
	Point2f GetCenter() const;


protected:

	Sprite* m_pSprite;
	Rectf m_DrawShape;
	Point2f m_Center;
};
