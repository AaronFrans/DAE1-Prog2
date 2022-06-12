#pragma once
#include <vector>

class Hearth;
class Texture;
class IsaacHealthBar final
{

public:

	IsaacHealthBar(Texture* heartSheet, float health, Point2f bottomLeft);

	IsaacHealthBar(const IsaacHealthBar& rhs) = default;
	IsaacHealthBar(IsaacHealthBar&& rhs) = default;
	IsaacHealthBar& operator=(const IsaacHealthBar& rhs) = default;
	IsaacHealthBar& operator=(IsaacHealthBar&& rhs) = default;
	~IsaacHealthBar();


	void DrawHealtBar(const Rectf& Camera, float offsetWidth) const;
	void TakeDamage(float damage);

	bool IsDead();
	bool IsFull();

	void AddHealth(float amount);
	void Heal(float healAmount);

private:

	std::vector<Hearth*> m_pHearts;
	Hearth* m_pEmptyHeart;
	float m_Health;
	float m_MaxHealth;
	float m_HeartSize;

};

