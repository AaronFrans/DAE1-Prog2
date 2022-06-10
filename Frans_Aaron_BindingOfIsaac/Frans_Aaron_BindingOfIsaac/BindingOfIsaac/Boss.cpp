#include "pch.h"
#include "Boss.h"
#include "BossHealthBar.h"

Boss::Boss(Point2f centerPoint, float damage, float speed, float health, Texture* healthBarTexture, SoundEffectManager* soundEffectManager)
	:Enemy{ centerPoint, damage, speed, health, soundEffectManager }
{
	m_pHealthBar = new BossHealthBar{ healthBarTexture , health };
}

Boss::Boss(Point2f centerPoint, float damage, float speed, float health, BossHealthBar* healthBar, SoundEffectManager* soundEffectManager)
	: Enemy{ centerPoint, damage, speed, health, soundEffectManager }
	, m_pHealthBar{ healthBar }
{
}

Boss::~Boss()
{
	delete m_pHealthBar;
	m_pHealthBar = nullptr;
}

BossHealthBar* Boss::GetHealthBar()
{
	return m_pHealthBar;
}
