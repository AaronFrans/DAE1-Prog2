#pragma once
#include <vector>

class Sprite;

class SpriteManager
{
public:
	SpriteManager();

	~SpriteManager();

	void UpdateSprites(float elapsedSec);

	void AddSprite(Sprite* sprite);

	size_t GetSize() const;

private:
	std::vector<Sprite* > m_pSprites;

};

