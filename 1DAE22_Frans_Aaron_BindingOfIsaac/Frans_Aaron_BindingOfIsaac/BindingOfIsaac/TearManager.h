#pragma once
#include "Tear.h"
#include <vector>

class Texture;

class TearManager final
{
public:
	TearManager();
	~TearManager();

	void DrawFrontTears() const;
	void DrawBackTears() const;
	void UpdateTears(float elapsedSec, std::vector<GameObject*> gameObjects);

	Tear* ShootTear();
private:

	const static int m_NrTears{ 100 };

	std::vector<Tear* > m_pTears;


};

