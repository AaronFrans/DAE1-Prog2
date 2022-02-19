#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	:m_Type{type}
	,m_RotSpeed{360.0f}
	,m_Angle{0.0f}
{

	m_Shape = Circlef {center, m_pTexture->GetWidth() / 2};
	switch (m_Type)
	{
	case Type::brown:
		m_TextClip = Rectf{ 0, m_pTexture->GetHeight(),  m_pTexture->GetWidth(), m_pTexture->GetHeight() / 2 };
		break;
	case Type::green:
		m_TextClip = Rectf{ 0, m_pTexture->GetHeight() / 2,  m_pTexture->GetWidth(), 0 };
		break;
	}	
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += elapsedSec * m_RotSpeed;
}

void PowerUp::Draw() const
{
	m_pTexture->Draw();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}
