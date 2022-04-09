#pragma once
#include <vector>

class Texture;

class TextureManager
{

public:

	enum class TextureLookup
	{
		//Isaac Textures
		isaacHead = 0,
		isaacBodyLR,
		isaacBodyUD,
		//Tear Textures
		isaacTearHit,
		isaacTear ,
		//GameObject Textures
		poop,
		//Room Textures
		roomBig,
		roomSmall,
		//Ui Textures
		hearths,
		//Enemy Textures
		smallSpiderMovement,
		smallSpiderDeath,

	};


	TextureManager();
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

