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
		isaacDying,
		//Tear Textures
		isaacTearHit,
		isaacTear ,
		//GameObject Textures
		poop,
		rock,
		itemPedestal,
		//Room Textures
		roomBig,
		roomSmall,
		basementDoorFrame,
		itemDoorFrame,
		basementDoorHallway,
		basementDoorLeft,
		basementDoorRight,
		bossDoorFrame,
		bossDoorHallway,
		bossDoorLeft,
		bossDoorRight,
		//Ui Textures
		hearths,
		//Enemy Textures
		smallSpiderMovement,
		smallSpiderDying,
		flyMovement,
		flyDying,
		//Boss Textures
		bossMonstro,
		//Items
		collectibleHeart,
		costumeHeartUD,
		costumeHeartLR,
		collectiblesBluecap,
		costumeBluecap,

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
	void InitBossTextures();
	void InitItemTextures();

};

