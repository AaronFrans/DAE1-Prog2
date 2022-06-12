#include "pch.h"
#include "MenuScreen.h"
#include "Texture.h"

MenuScreen::MenuScreen(Texture* backgroundTexture, std::string text, std::string fontPath,
	Rectf screenSize)
	: m_pBackgroundTexture{ backgroundTexture }
	, m_ScreenSize{ screenSize }
{
	m_pMenuText = new Texture{ text, fontPath,
		25, Color4f{0.3f,0.3f,0.3f,1} };
}

MenuScreen::~MenuScreen()
{
	delete m_pMenuText;
	m_pMenuText;
}

void MenuScreen::Draw() const
{
	Point2f bgBottomLeft{
		m_ScreenSize.left + m_ScreenSize.width / 2.0f - m_pBackgroundTexture->GetWidth() / 2.0f,
		m_ScreenSize.bottom + m_ScreenSize.height / 2.0f - m_pBackgroundTexture->GetHeight() / 2.0f
	};

	m_pBackgroundTexture->Draw(bgBottomLeft);

	Point2f textBottomLeft{
		m_ScreenSize.left + m_ScreenSize.width / 2.0f - m_pMenuText->GetWidth() / 2.0f,
		bgBottomLeft.y - m_pMenuText->GetHeight() / 2.0f - 30
	};

	m_pMenuText->Draw(textBottomLeft);

}
