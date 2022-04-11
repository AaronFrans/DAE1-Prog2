#pragma once

class IsaacHealthBar;
class UIManager final
{
public:

	UIManager(IsaacHealthBar* pIsaacHealthBar);
	~UIManager();
	void Draw(const Rectf& camera) const;


private:

	IsaacHealthBar* m_pIsaacHealtBar;

};

