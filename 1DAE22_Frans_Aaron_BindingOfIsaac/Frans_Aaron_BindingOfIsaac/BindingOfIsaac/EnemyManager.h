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

	EnemyManager(const TextureManager& textureManager);

	EnemyManager(const EnemyManager& rhs) = default;
	EnemyManager(EnemyManager && rhs) = default;
	EnemyManager& operator=(const EnemyManager & rhs) = default;
	EnemyManager& operator=(EnemyManager && rhs) = default;
	~EnemyManager();



	Enemy* GetRandomEnemy(Floor floor) const;

private:

	std::vector<std::vector<Enemy*>> m_pFloorEnemies;
	void AddBasementEnemies(const TextureManager& textureManager);
};

