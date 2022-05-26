#include "pch.h"
#include "ItemManager.h"
#include "Item.h"
#include "Texture.h"
#include "Sprite.h"
#include "utils.h"
#include <map>

ItemManager::ItemManager(const TextureManager& textureManager)
{
	MakeItemPool(textureManager);
}

ItemManager::~ItemManager()
{
	for (Item* item : m_pItemPool)
	{
		delete item;
	}
	for (Item* item : m_pPickedUpItems)
	{
		delete item;
	}


}

Item* ItemManager::GetRandomItem()
{

	int index{ utils::GetRand(0, (int)m_pItemPool.size() - 1) };
	return m_pItemPool[index];
}

void ItemManager::PickUpItem(std::string name)
{
	int index{};
	int nrItems{ (int)m_pItemPool.size() - 1 };
	Item* pTemp;
	for (int i = 0; i < nrItems; i++)
	{
		if (m_pItemPool[i]->GetName() == name)
		{
			index = i;
		}
	}

	pTemp = m_pItemPool[index];
	m_pItemPool[index] = m_pItemPool[nrItems];
	m_pItemPool[nrItems] = pTemp;

	m_pPickedUpItems.push_back(pTemp);

	m_pItemPool.pop_back();

}

void ItemManager::MakeItemPool(const TextureManager& textureManager)
{
	std::map<Item::StatChanges, float> statChanges{};

	statChanges[Item::StatChanges::walkSpeed] = 0;
	statChanges[Item::StatChanges::tearHeight] = 0;
	statChanges[Item::StatChanges::tearSpeed] = 0;
	statChanges[Item::StatChanges::tearRange] = 0;
	statChanges[Item::StatChanges::damage] = 0;
	statChanges[Item::StatChanges::tearFireRate] = 0;
	statChanges[Item::StatChanges::healthCointainer] = 0;

	Texture* pickUpTexture = nullptr;
	Sprite* costumeUD = nullptr;
	Sprite* costumeLR = nullptr;
	float costumeFrameRate{ 1 / 7.0f };

#pragma region Heart

	statChanges[Item::StatChanges::healthCointainer] = 1;

	pickUpTexture = textureManager.GetTexture(TextureManager::TextureLookup::collectibleHeart);

	costumeUD = new Sprite(textureManager.GetTexture(TextureManager::TextureLookup::costumeHeartUD),
		5, 1, costumeFrameRate, 1);

	costumeLR = new Sprite(textureManager.GetTexture(TextureManager::TextureLookup::costumeHeartLR),
		3, 1, costumeFrameRate, 1);

	m_pItemPool.push_back(new Item("Heart", pickUpTexture, costumeUD, costumeLR,
		Point2f{ 0,0 }, statChanges, Item::CostumeType::body));

	statChanges[Item::StatChanges::healthCointainer] = 0;

#pragma endregion


#pragma region Blue-Cap

	statChanges[Item::StatChanges::healthCointainer] = 1;
	statChanges[Item::StatChanges::tearFireRate] = 0.7f;
	statChanges[Item::StatChanges::tearSpeed] = -0.16f;

	pickUpTexture = textureManager.GetTexture(TextureManager::TextureLookup::collectiblesBluecap);

	costumeUD = new Sprite(textureManager.GetTexture(TextureManager::TextureLookup::costumeBluecap),
		8, 1, costumeFrameRate, 1);

	costumeLR = new Sprite(*costumeUD);

	m_pItemPool.push_back(new Item("Blue Cap", pickUpTexture, costumeUD, costumeLR,
		Point2f{ 0,0 }, statChanges, Item::CostumeType::head));

	statChanges[Item::StatChanges::healthCointainer] = 0;
	statChanges[Item::StatChanges::tearFireRate] = 0;
	statChanges[Item::StatChanges::tearSpeed] = 0;

#pragma endregion


}
