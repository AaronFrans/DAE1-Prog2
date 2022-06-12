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
		isaacTear,
		enemyTear,
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
		uiHearths,
		uiBossHealthBar,
		uiMinimap,
		uiMinimapRooms,
		uiMinimapRoomItem,
		uiMinimapRoomBoss,
		//Menus
		startMenu,
		deathScreen,
		victoryScreen,
		//Enemy Textures
		smallSpiderMovement,
		smallSpiderDying,
		flyMovement,
		flyDying,
		//Boss Textures
		bossMonstro,
		bossDeathBlood,
		//Items
		collectibleHeart,
		costumeHeartUD,
		costumeHeartLR,
		collectiblesBluecap,
		costumeBluecap,
		//Shared
		shadow,
		//PickUps
		pickupFullHeart,
		pickupHalfHeart,

	};


	TextureManager();

	TextureManager(const TextureManager& rhs) = default;
	TextureManager(TextureManager && rhs) = default;
	TextureManager& operator=(const TextureManager & rhs) = default;
	TextureManager& operator=(TextureManager && rhs) = default;
	~TextureManager();

	Texture* GetTexture(TextureLookup textureName) const;

private:

	std::vector<Texture*> m_pTextures;

	void InitTextures();
	void InitIsaacTextures();
	void InitTearTextures();
	void InitGameObjectTextures();
	void InitRoomTextures();
	void InitUiTextures();
	void InitMenuTextures();
	void InitEnemyTextures();
	void InitBossTextures();
	void InitItemTextures();
	void InitSharedTextures();
	void InitPickUpTextures();

};

