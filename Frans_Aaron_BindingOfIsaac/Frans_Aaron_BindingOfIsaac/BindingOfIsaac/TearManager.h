#pragma once
#include <vector>

class Enemy;
class Tear;
class GameObject;
class ItemPedestal;
class Isaac;
class Room;
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
	void UpdateTears(float elapsedSec, Room* currentRoom, Isaac* isaac);

	Tear* ShootTear();

	void ClearTears();
private:

	const static int m_NrTears{ 100 };

	std::vector<Tear* > m_pTears;


};

