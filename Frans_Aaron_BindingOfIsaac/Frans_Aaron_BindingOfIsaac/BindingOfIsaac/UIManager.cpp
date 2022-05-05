#include "pch.h"
#include "UIManager.h"
#include "IsaacHealthBar.h"

UIManager::UIManager(IsaacHealthBar* pIsaacHealthBar)
	: m_pIsaacHealtBar{ pIsaacHealthBar }
{
}

UIManager::~UIManager()
{
	delete m_pIsaacHealtBar;
}

void UIManager::Draw(const Rectf& camera) const
{
	m_pIsaacHealtBar->DrawHealtBar(camera);
}
