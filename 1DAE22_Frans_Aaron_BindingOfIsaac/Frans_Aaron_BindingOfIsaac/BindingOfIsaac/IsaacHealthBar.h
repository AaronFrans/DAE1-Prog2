#pragma once
#include <vector>

class Hearth;
class Texture;
class IsaacHealthBar final
{

public:

	IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft);
	~IsaacHealthBar();

	void DrawHealtBar(const Rectf& Camera) const;

	void TakeDamage(float damage);

private:

	std::vector<Hearth*> m_pHearts;

	float m_Health;
	float m_HeartSize;

};

