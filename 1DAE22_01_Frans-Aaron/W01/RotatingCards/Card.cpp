#include "pch.h"
#include "Card.h"
#include "Texture.h"

#include <math.h>

#define _USE_MATH_DEFINES

Card::Card(Suit suit, int rank, float angle, Circlef circle)
	: m_Suit{ suit }
	, m_Rank{ rank }
	, m_AngleDegree{angle}
	, m_Circle{circle}
{
	m_pTexture = new Texture(this->GetImagePath(suit, rank));
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();

}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Draw(const Rectf& destRect) const
{

	glPushMatrix();
	glTranslatef(m_Circle.center.x, m_Circle.center.y, 0);
	glRotatef(-m_AngleDegree, 0, 0, 1);
	glTranslatef(-(destRect.width / 2), -(destRect.height / 2), 0);
	glTranslatef(
		m_Circle.radius,
		0,
		0);

	m_pTexture->Draw(destRect, Rectf{ 0, 0, m_Width, m_Height });

	glPopMatrix();


}

void Card::Update(float elapsedSec)
{
	m_AngleDegree -= 180 * elapsedSec;
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	std::string path{ 
		"../Resources/Images/Cards/" +
		std::to_string((int)suit * 100 + rank) +
		".png"
	};
	return path;
}
