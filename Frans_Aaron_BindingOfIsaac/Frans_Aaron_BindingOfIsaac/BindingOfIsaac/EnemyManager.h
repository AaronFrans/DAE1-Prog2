#pragma once
#include <vector>
#include "Enemy.h"

class TextureManager;
class EnemyManager
{
public:
	enum class Floor
	{
		basement = 0,
		count,
	};

	EnemyManager(const TextureManager& textureManager, SoundEffectManager* soundEffectManager);

	EnemyManager(const EnemyManager& rhs) = default;
	EnemyManager(EnemyManager && rhs) = default;
	EnemyManager& operator=(const EnemyManager & rhs) = default;
	EnemyManager& operator=(EnemyManager && rhs) = default;
	~EnemyManager();



	Enemy* GetRandomEnemy(Floor floor) const;
	Enemy* GetRandomBoss(Floor floor) const;

private:

	std::vector<std::vector<Enemy*>> m_pFloorEnemies;
	std::vector<std::vector<Enemy*>> m_pBosses;

	void AddBasementEnemies(const TextureManager& textureManager, SoundEffectManager* soundEffectManager);
	void AddBasementBosses(const TextureManager& textureManager, SoundEffectManager* soundEffectManager);
};

