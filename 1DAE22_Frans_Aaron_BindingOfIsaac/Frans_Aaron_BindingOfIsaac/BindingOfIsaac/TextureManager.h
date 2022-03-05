#pragma once
#include <vector>

class Texture;

class TextureManager
{

public:

	enum class TextureLookup
	{
		IsaacHead = 0,
		IsaacBodyLR = 1,
		IsaacBodyUD = 2,
		TearHit = 3,
		Tears = 4,

	};


	TextureManager();
	~TextureManager();

	Texture* GetTexture(TextureLookup lookup) const;

private:

	std::vector<Texture*> m_pTextures;

	void InitTextures();
	void InitIsaacTextures();
	void InitTearTextures();

};

