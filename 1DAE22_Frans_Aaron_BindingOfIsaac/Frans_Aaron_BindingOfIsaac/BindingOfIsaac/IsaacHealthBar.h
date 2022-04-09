#pragma once
#include <vector>

class Hearth;
class Texture;
class IsaacHealthBar
{

public:

	IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft);
	~IsaacHealthBar();

	void DrawHealtBar(const Rectf& Camera) const;

private:

	std::vector<Hearth*> m_pHearts;

	float m_Health;
	float m_HeartSize;

};

