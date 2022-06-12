#include "pch.h"
#include "PickUp.h"
#include "Texture.h"
#include "utils.h"
#include "Isaac.h"

PickUp::PickUp(Texture* texture, Type type, Point2f centerPos)
	: m_pTexture{ texture }
	, m_Type{ type }
	, m_CenterPos{ centerPos }
{

	m_DrawWidth = m_pTexture->GetWidth();
	m_DrawHeight = m_pTexture->GetHeight();

	m_ShapeSize = m_DrawWidth / 2.0f;
}

void PickUp::Draw() const
{
	m_pTexture->Draw(Point2f{
		m_CenterPos.x - m_DrawWidth / 2.0f,
		m_CenterPos.y - m_DrawHeight / 2.0f
		});
	utils::DrawEllipse(GetShape().center, GetShape().radius, GetShape().radius);
}

bool PickUp::HasIsaacCollision(Isaac* isaac)
{
	if (!isaac->IsFullHealth() &&
		utils::IsOverlapping(isaac->GetHitBox(), GetShape()))
	{
		switch (m_Type)
		{
		case PickUp::Type::fullHeart:
				isaac->Heal(1);
			return true;
			break;
		case PickUp::Type::halfHeart:
			isaac->Heal(0.5f);
			return true;
			break;
		}
	}

	return false;
}

Circlef PickUp::GetShape() const
{
	return Circlef{ m_CenterPos, m_ShapeSize };
}
