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
		IsaacBodyUD = 2

	};


	TextureManager();
	~TextureManager();

	Texture* GetTexture(TextureLookup lookup) const;

private:

	std::vector<Texture*> m_pTextures;

	void InitTextures();
	void InitIsaacTextures();

};

