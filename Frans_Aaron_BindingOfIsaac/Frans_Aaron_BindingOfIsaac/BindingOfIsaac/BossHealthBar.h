#pragma once
class Texture;
class BossHealthBar
{
public:

	BossHealthBar(Texture* healthBar, float health);

	BossHealthBar(const BossHealthBar& rhs);
	BossHealthBar(BossHealthBar && rhs) = default;
	BossHealthBar& operator=(const BossHealthBar & rhs);
	BossHealthBar& operator=(BossHealthBar && rhs) = default;
	virtual ~BossHealthBar() = default;


	void DrawHealtBar(const Rectf& Camera) const;
	void TakeDamage(float damage);

private:

	Texture* m_pHealthBar;
	float m_Health;
	float m_MaxHealth;

	float m_SrcWidth;
	float m_SrcHeight;
};

