#pragma once
#include "Tear.h"
#include <vector>

class Texture;

class TearManager
{
public:
	TearManager(Texture* texture);
	~TearManager();

	void DrawTears() const;
	void UpdateTears(float elapsedSec);

	Tear* ShootTear();
private:

	const static int m_NrTears{ 100 };

	int m_NrShotTears;

	std::vector<Tear* > m_pTears;


};

