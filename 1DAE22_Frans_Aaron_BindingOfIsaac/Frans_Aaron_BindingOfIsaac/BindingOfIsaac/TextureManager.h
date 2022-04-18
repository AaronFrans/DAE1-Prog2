#pragma once
#include <vector>

class Texture;

class TextureManager final
{

public:

	enum class TextureLookup
	{
		//Isaac Textures
		isaacHead = 0,
		isaacBodyLR,
		isaacBodyUD,
		isaacHurt,
		//Tear Textures
		isaacTearHit,
		isaacTear ,
		//GameObject Textures
		poop,
		rock,
		//Room Textures
		roomBig,
		roomSmall,
		//Ui Textures
		hearths,
		//Enemy Textures
		smallSpiderMovement,
		smallSpiderDying,
		flyMovement,
		flyDying,

	};


	TextureManager();

	TextureManager(const TextureManager& rhs) = default;
	TextureManager(TextureManager && rhs) = default;
	TextureManager& operator=(const TextureManager & rhs) = default;
	TextureManager& operator=(TextureManager && rhs) = default;
	~TextureManager();

	Texture* GetTexture(TextureLookup lookup) const;

private:

	std::vector<Texture*> m_pTextures;

	void InitTextures();
	void InitIsaacTextures();
	void InitTearTextures();
	void InitGameObjectTextures();
	void InitRoomTextures();
	void InitUi();
	void InitEnemyTextures();

};

