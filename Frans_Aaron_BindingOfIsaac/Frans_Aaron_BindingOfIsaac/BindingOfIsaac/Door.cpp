#include "pch.h"
#include "Door.h"
#include "Texture.h"
#include "TextureManager.h"
#include "utils.h"

Door::Door(const TextureManager& textureManager, Point2f center, DoorState state, DoorDirection direction, Rectf shape)
	: m_Center{ center }
	, m_State{ state }
	, m_Direction{ direction }
	, m_IsActive{ false }
	, m_Shape{shape}
{
	m_pDoorFrame = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorFrame);

	m_Width = m_pDoorFrame->GetWidth();
	m_Height = m_pDoorFrame->GetHeight();

	m_pDoorHallway = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorHallway);

	m_HallwayWidth = m_pDoorHallway->GetWidth();
	m_HallwayHeight = m_pDoorHallway->GetHeight();


	m_pDoorRight = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorRight);
	m_pDoorLeft = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorLeft);
}

Door::Door(const Door& rhs)
	: m_Center{ rhs.m_Center }
	, m_State{ rhs.m_State }
	, m_Direction{ rhs.m_Direction }
	, m_IsActive{ rhs.m_IsActive }
	, m_Shape{rhs.m_Shape}
{
	m_pDoorFrame = rhs.m_pDoorFrame;
	m_Width = rhs.m_Width;
	m_Height = rhs.m_Height;

	m_pDoorHallway = rhs.m_pDoorHallway;

	m_HallwayWidth = rhs.m_HallwayWidth;
	m_HallwayHeight = rhs.m_HallwayHeight;


	m_pDoorRight = rhs.m_pDoorRight;
	m_pDoorLeft = rhs.m_pDoorLeft;

}

Door& Door::operator=(const Door& rhs)
{
	m_Center = rhs.m_Center;
	m_State = rhs.m_State;
	m_Direction = rhs.m_Direction;
	m_IsActive = rhs.m_IsActive;
	m_Shape = rhs.m_Shape;

	m_pDoorFrame = rhs.m_pDoorFrame;
	m_Width = rhs.m_Width;
	m_Height = rhs.m_Height;

	m_pDoorHallway = rhs.m_pDoorHallway;

	m_HallwayWidth = rhs.m_HallwayWidth;
	m_HallwayHeight = rhs.m_HallwayHeight;


	m_pDoorRight = rhs.m_pDoorRight;
	m_pDoorLeft = rhs.m_pDoorLeft;

	return *this;
}



void Door::Draw() const
{

	if (m_IsActive)
	{
		switch (m_Direction)
		{
		case Door::DoorDirection::up:
			DrawUp();
			break;
		case Door::DoorDirection::down:
			DrawDown();
			break;
		case Door::DoorDirection::left:
			DrawLeft();
			break;
		case Door::DoorDirection::right:
			DrawRight();
			break;
		}
	}


}

void Door::Update(float elapsedSec)
{
	switch (m_State)
	{
	case Door::DoorState::opening:
		break;
	case Door::DoorState::closing:
		break;
	default:
		break;
	}
}

void Door::SetState(DoorState state)
{
	m_State = state;
}

void Door::Activate()
{
	m_IsActive = true;
}

Door::DoorDirection Door::GetDirection()
{
	return m_Direction;
}

Rectf Door::GetShape() const
{
	return m_Shape;
}

bool Door::IsActive() const
{
	return m_IsActive;
}

void Door::SetRoomOrigin(const Point2f& roomOrigin)
{
	m_Center.x += roomOrigin.x;
	m_Center.y += roomOrigin.y;
	m_Shape.left += roomOrigin.x;
	m_Shape.bottom += roomOrigin.y;
}

void Door::DrawUp() const
{
	DrawSprite();
}

void Door::DrawLeft() const
{
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-m_Center.x, -m_Center.y, 0);
	DrawSprite();
	glPopMatrix();
}

void Door::DrawDown() const
{
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, 0);
	glScalef(1, -1, 1);
	glTranslatef(-m_Center.x, -m_Center.y, 0);
	DrawSprite();
	glPopMatrix();
}

void Door::DrawRight() const
{
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, 0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-m_Center.x, -m_Center.y, 0);
	DrawSprite();
	glPopMatrix();
}

void Door::DrawSprite() const
{
	m_pDoorHallway->Draw(Point2f{ m_Center.x - m_HallwayWidth / 2.0f, m_Center.y - m_Height / 2.0f });

	if (m_State == DoorState::closed)
	{
		m_pDoorLeft->Draw(Point2f{ m_Center.x - m_Width / 4.0f, m_Center.y - m_Height / 2.0f });
		m_pDoorRight->Draw(Point2f{ m_Center.x, m_Center.y - m_Height / 2.0f });
	}
	m_pDoorFrame->Draw(Point2f{ m_Center.x - m_Width / 2.0f, m_Center.y - m_Height / 2.0f });
}
