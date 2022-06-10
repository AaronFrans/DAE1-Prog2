#pragma once
#include <vector>

class IsaacHealthBar;
class BossHealthBar;
class Minimap;
class UIManager final
{
public:

	UIManager(IsaacHealthBar* pIsaacHealthBar, Minimap* minimap);

	UIManager(const UIManager& rhs) = default;
	UIManager(UIManager&& rhs) = default;
	UIManager& operator=(const UIManager& rhs) = default;
	UIManager& operator=(UIManager&& rhs) = default;
	~UIManager();

	void Draw(const Rectf& camera) const;

	void SetBossHealthBar(BossHealthBar* healthBar);

	void UpdateMinimap(std::pair<int, int> newIndexes);


private:

	IsaacHealthBar* m_pIsaacHealtBar;
	BossHealthBar* m_pBossHealthBar;
	Minimap* m_pMap;

};

