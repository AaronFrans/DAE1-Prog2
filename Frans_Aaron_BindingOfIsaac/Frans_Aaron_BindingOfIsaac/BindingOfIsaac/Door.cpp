#include "pch.h"
#include "Door.h"
#include "Texture.h"
#include "TextureManager.h"

Door::Door(const TextureManager& textureManager, Point2f center, DoorState state, DoorDirection direction)
	: m_Center{ center }
	, m_State{ state }
	, m_Direction{ direction }
{
	m_pDoorFrame = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorFrame);

	m_Width = m_pDoorFrame->GetWidth();
	m_Height = m_pDoorFrame->GetHeight();

	m_pDoorHallway = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorHallway);

	m_HallwayWidth = m_pDoorHallway->GetWidth();
	m_HallwayHeight = m_pDoorHallway->GetHeight();


	m_pDoorRight = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorRight);
	m_pDoorLeft = textureManager.GetTexture(TextureManager::TextureLookup::basementDoorLeft);

	m_temp = 0;
}



void Door::Draw() const
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

void Door::DrawUp() const
{
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, 0);
	glScalef(1, -1, 1);
	glTranslatef(-m_Center.x, -m_Center.y, 0);
	DrawSprite();
	glPopMatrix();
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
	DrawSprite();
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
