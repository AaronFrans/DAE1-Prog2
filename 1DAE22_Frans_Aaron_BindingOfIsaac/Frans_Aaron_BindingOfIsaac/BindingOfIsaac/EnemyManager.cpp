#include "pch.h"
#include "EnemyManager.h"
#include "TextureManager.h"
#include "SmallSpider.h"
#include "Fly.h"
#include "utils.h"

EnemyManager::EnemyManager(const TextureManager& textureManager)
{
	AddBasementEnemies(textureManager);
}

EnemyManager::~EnemyManager()
{
	for (std::vector<Enemy*> floor : m_pFloorEnemies)
	{
		for (Enemy* enemy : floor)
		{
			delete enemy;
		}
	}
}

Enemy* EnemyManager::GetRandomEnemy(Floor floor) const
{
	int randomIndexMax{ (int)m_pFloorEnemies[(int)floor].size() - 1 };
	int randomIndex{ utils::GetRand(0, randomIndexMax) };
	return m_pFloorEnemies[(int)floor][randomIndex];
}


void EnemyManager::AddBasementEnemies(const TextureManager& textureManager)
{
	m_pFloorEnemies.push_back(std::vector<Enemy*>{});

	m_pFloorEnemies[(int)Floor::basement].push_back(new SmallSpider{
		textureManager.GetTexture(TextureManager::TextureLookup::smallSpiderMovement),
		textureManager.GetTexture(TextureManager::TextureLookup::smallSpiderDying),
		Point2f{ 0,0 } });

	m_pFloorEnemies[(int)Floor::basement].push_back(new Fly{
		textureManager.GetTexture(TextureManager::TextureLookup::flyMovement),
		textureManager.GetTexture(TextureManager::TextureLookup::flyDying),
		Point2f{ 0,0 } });

}
