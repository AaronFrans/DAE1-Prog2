#pragma once
#include "TextureManager.h"
#include <vector>

class Item;
class ItemManager
{

public:
	ItemManager(const TextureManager& textureManager);

	ItemManager(const ItemManager& rhs) = default;
	ItemManager(ItemManager && rhs) = default;
	ItemManager& operator=(const ItemManager & rhs) = default;
	ItemManager& operator=(ItemManager && rhs) = default;
	~ItemManager();


	Item* GetRandomItem();

	void PickUpItem(std::string name);

private:

	std::vector<Item*> m_pItemPool;
	std::vector<Item*> m_pPickedUpItems;


	void MakeItemPool(const TextureManager& textureManager);
};

