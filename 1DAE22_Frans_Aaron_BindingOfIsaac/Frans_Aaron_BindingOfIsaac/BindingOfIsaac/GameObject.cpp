#include "pch.h"
#include "GameObject.h"
#include "Sprite.h"


GameObject::GameObject(Texture* objectTexture, int nrColls, int nrRows, Point2f center, float size)
	: m_Center{ center }
	, m_Shape{ center.x - size / 2.0f, center.y - size / 2.0f, size, size }
{
	m_pSprite = new Sprite(objectTexture, nrColls, nrRows, 0, 1, 1);

}

GameObject::~GameObject()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

Rectf GameObject::GetShape() const
{
	return m_Shape;
}



