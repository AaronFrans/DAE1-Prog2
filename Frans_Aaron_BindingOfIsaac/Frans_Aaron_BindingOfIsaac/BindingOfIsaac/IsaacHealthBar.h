#pragma once
#include <vector>

class Hearth;
class Texture;
class IsaacHealthBar final
{

public:

	IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft);

	IsaacHealthBar(const IsaacHealthBar& rhs) = default;
	IsaacHealthBar(IsaacHealthBar && rhs) = default;
	IsaacHealthBar& operator=(const IsaacHealthBar & rhs) = default;
	IsaacHealthBar& operator=(IsaacHealthBar && rhs) = default;
	~IsaacHealthBar();


	void DrawHealtBar(const Rectf& Camera) const;

	void TakeDamage(float damage);

	bool IsDead();

private:

	std::vector<Hearth*> m_pHearts;

	float m_Health;
	float m_HeartSize;

};

