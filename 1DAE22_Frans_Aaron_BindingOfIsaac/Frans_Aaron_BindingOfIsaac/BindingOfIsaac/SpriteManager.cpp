#include "pch.h"
#include "SpriteManager.h"
#include "Sprite.h"


SpriteManager::SpriteManager()
	: m_pSprites{}
{
}

SpriteManager::~SpriteManager()
{
	for (Sprite* sprite : m_pSprites)
		delete sprite;
	m_pSprites.clear();
}

void SpriteManager::UpdateSprites(float elapsedSec)
{
	for (Sprite* sprite : m_pSprites)
		sprite->Update(elapsedSec);
}

void SpriteManager::AddSprite(Sprite* sprite)
{
	m_pSprites.push_back(sprite);
}

size_t SpriteManager::GetSize() const
{
	return m_pSprites.size();
}
