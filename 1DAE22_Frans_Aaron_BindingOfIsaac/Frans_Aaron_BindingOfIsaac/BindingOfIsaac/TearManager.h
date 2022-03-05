#pragma once
#include "Tear.h"
#include <vector>


class TearManager
{
public:
	TearManager();
	~TearManager();

	void DrawTears() const;
	void UpdateTears(float elapsedSec);

	void ShootTear(const Point2f& tearPos, const float& tearRadius, const Vector2f& tearVelocity, const float& tearHeight);
private:

	const static int m_NrTears{ 100 };

	int m_NrShotTears;

	std::vector<Tear* > m_pTears;


};

