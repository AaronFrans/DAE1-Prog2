#include "pch.h"
#include "EnemyManager.h"
#include "TextureManager.h"
#include "SmallSpider.h"
#include "Fly.h"
#include "Monstro.h"
#include "utils.h"

EnemyManager::EnemyManager(const TextureManager& textureManager, SoundEffectManager* soundEffectManager)
{
	AddBasementEnemies(textureManager, soundEffectManager);
	AddBasementBosses(textureManager, soundEffectManager);
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

	for (std::vector<Enemy*> floor : m_pBosses)
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

Enemy* EnemyManager::GetRandomBoss(Floor floor) const
{
	int randomIndexMax{ (int)m_pBosses[(int)floor].size() - 1 };
	int randomIndex{ utils::GetRand(0, randomIndexMax) };
	return m_pBosses[(int)floor][randomIndex];
}


void EnemyManager::AddBasementEnemies(const TextureManager& textureManager, SoundEffectManager* soundEffectManager)
{
	m_pFloorEnemies.push_back(std::vector<Enemy*>{});

	m_pFloorEnemies[(int)Floor::basement].push_back(new SmallSpider{
		textureManager.GetTexture(TextureManager::TextureLookup::smallSpiderMovement),
		textureManager.GetTexture(TextureManager::TextureLookup::smallSpiderDying),
		Point2f{ 0,0 }, soundEffectManager });

	m_pFloorEnemies[(int)Floor::basement].push_back(new Fly{
		textureManager.GetTexture(TextureManager::TextureLookup::flyMovement),
		textureManager.GetTexture(TextureManager::TextureLookup::flyDying),
		Point2f{ 0,0 }, soundEffectManager });

}

void EnemyManager::AddBasementBosses(const TextureManager& textureManager, SoundEffectManager* soundEffectManager)
{
	m_pBosses.push_back(std::vector<Enemy*>{});

	m_pBosses[(int)Floor::basement].push_back(new Monstro{ 
		textureManager.GetTexture(TextureManager::TextureLookup::bossMonstro),
		textureManager.GetTexture(TextureManager::TextureLookup::shadow),
		textureManager.GetTexture(TextureManager::TextureLookup::uiBossHealthBar),
		textureManager.GetTexture(TextureManager::TextureLookup::bossDeathBlood),
		Point2f{0,0}, soundEffectManager
		});


}
