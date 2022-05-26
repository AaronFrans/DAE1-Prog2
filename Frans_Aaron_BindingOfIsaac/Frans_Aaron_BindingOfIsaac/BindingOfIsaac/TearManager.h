#pragma once
#include <vector>

class Enemy;
class Tear;
class GameObject;
class ItemPedestal;
class TearManager final
{
public:
	TearManager();

	TearManager(const TearManager& rhs) = default;
	TearManager(TearManager && rhs) = default;
	TearManager& operator=(const TearManager & rhs) = default;
	TearManager& operator=(TearManager && rhs) = default;
	~TearManager();

	void DrawFrontTears() const;
	void DrawBackTears() const;
	void UpdateTears(float elapsedSec, std::vector<GameObject*> gameObjects, std::vector<Enemy*> enemies, std::vector<ItemPedestal*> pedestals);

	Tear* ShootTear();
private:

	const static int m_NrTears{ 100 };

	std::vector<Tear* > m_pTears;


};

