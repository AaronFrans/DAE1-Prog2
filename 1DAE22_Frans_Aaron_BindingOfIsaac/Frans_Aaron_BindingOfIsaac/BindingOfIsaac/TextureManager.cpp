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
}

void TextureManager::InitIsaacTextures()
{
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Head.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Walk-LR.png" });
	m_pTextures.push_back(new Texture{ "Resources/Images/Isaac/Isaac-Walk-UD.png" });
}
