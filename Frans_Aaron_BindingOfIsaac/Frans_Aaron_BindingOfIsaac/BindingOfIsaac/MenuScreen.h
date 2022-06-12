#pragma once

class Texture;
class MenuScreen final
{

public:

	MenuScreen(Texture* backgroundTexture, std::string text, std::string fontPath,
		Rectf screenSize);

	MenuScreen(const MenuScreen& rhs) = default;
	MenuScreen(MenuScreen && rhs) = default;
	MenuScreen& operator=(const MenuScreen & rhs) = default;
	MenuScreen& operator=(MenuScreen && rhs) = default;
	~MenuScreen();


	
	void Draw() const;

private:
	
	Texture* m_pBackgroundTexture;
	Texture* m_pMenuText;


	Rectf m_ScreenSize;

};

