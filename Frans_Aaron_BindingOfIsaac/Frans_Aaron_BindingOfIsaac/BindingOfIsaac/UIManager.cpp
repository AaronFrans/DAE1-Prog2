#include "pch.h"
#include "UIManager.h"
#include "IsaacHealthBar.h"
#include "BossHealthBar.h"
#include "Minimap.h"

UIManager::UIManager(IsaacHealthBar* pIsaacHealthBar, Minimap* minimap)
	: m_pIsaacHealtBar{ pIsaacHealthBar }
	, m_pMap{ minimap }
	, m_pBossHealthBar{ nullptr }
{
}

UIManager::~UIManager()
{
	delete m_pIsaacHealtBar;
	delete m_pMap;
}

void UIManager::Draw(const Rectf& camera) const
{
	m_pMap->Draw(Point2f{
		camera.left + camera.width - 20,
		camera.bottom + camera.height - 20
		});

	m_pIsaacHealtBar->DrawHealtBar(camera, 20);

	if (m_pBossHealthBar != nullptr)
	{
		m_pBossHealthBar->DrawHealtBar(camera);
	}

}

void UIManager::SetBossHealthBar(BossHealthBar* healthBar)
{
	m_pBossHealthBar = healthBar;
}

void UIManager::UpdateMinimap(std::pair<int, int> newIndexes)
{
	m_pMap->MoveRoom(newIndexes);
}
