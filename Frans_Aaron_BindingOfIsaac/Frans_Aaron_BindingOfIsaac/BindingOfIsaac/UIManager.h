#pragma once

class IsaacHealthBar;
class UIManager final
{
public:

	UIManager(IsaacHealthBar* pIsaacHealthBar);

	UIManager(const UIManager& rhs) = default;
	UIManager(UIManager && rhs) = default;
	UIManager& operator=(const UIManager & rhs) = default;
	UIManager& operator=(UIManager && rhs) = default;
	~UIManager();

	void Draw(const Rectf& camera) const;


private:

	IsaacHealthBar* m_pIsaacHealtBar;

};

