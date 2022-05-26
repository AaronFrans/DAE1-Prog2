#include "pch.h"
#include "TextureManager.h"
#include"Texture.h"

TextureManager::TextureManager()
{

	InitTextures();

}

TextureManager::~TextureManager()
{

	for (size_t i = 0; i < m_pTextures.size(); i++)
	{
		delete m_pTextures[i];
		m_pTextures[i] = nullptr;
	}

}

Texture* TextureManager::GetTexture(TextureLookup lookup) const
{

	if ((int)lookup > m_pTextures.size() - 1)
	{
		return nullptr;
	}

	return m_pTextures[(int)lookup];

}

void TextureManager::InitTextures()
{

	InitIsaacTextures();
	InitTearTextures();
	InitGameObjectTextures();
	InitRoomTextures();
	InitUi();
	InitEnemyTextures();
	InitItemTextures();
}

void TextureManager::InitIsaacTextures()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Head.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Walk-LR.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Walk-UD.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Hurt.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Dying.png" });

}

void TextureManager::InitTearTextures()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Tears/Isaac-Tear-Hit.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Tears/Isaac-Tear.png" });

}

void TextureManager::InitGameObjectTextures()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/GameObjects/Poop.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/GameObjects/Rocks-Basement.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/GameObjects/Item-Pedestal.png" });

}

void TextureManager::InitRoomTextures()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Room-Big.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Room-Small.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Door-Frame.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Item-Door-Frame.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Door-Hallway.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Door-Left.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Basement-Door-Right.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Boss-Door-Frame.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Boss-Door-Hallway.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Boss-Door-Left.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Boss-Door-Right.png" });

}

void TextureManager::InitUi()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Ui/Ui_Hearts.png" });

}

void TextureManager::InitEnemyTextures()
{

	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Enemies/Spider-Small-Movement.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Enemies/Spider-Small-Death.png" });

	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Enemies/Fly-Movement.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Rooms/Enemies/Fly-Death.png" });

}

void TextureManager::InitItemTextures()
{
	m_pTextures.push_back(new Texture{ "Resources/Images/Items/Collectibles-Heart.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Items/Costume-Heart-UD.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Items/Costume-Heart-LR.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Items/Collectibles-Bluecap.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Items/Costume-Bluecap.png" });
}
