#include "pch.h"
#include "PowerUpManager.h"
#include "PowerUp.h"

PowerUpManager::PowerUpManager()
	: m_pItems{}
{
}

PowerUpManager::~PowerUpManager()
{
	for (int i = 0; i < Size(); i++)
	{
		delete m_pItems[i];
		m_pItems[i] = nullptr;
	}
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* p_Temp = new PowerUp{ center, type };

	m_pItems.push_back(p_Temp);

	return p_Temp;
}

void PowerUpManager::Draw() const
{
	for (PowerUp* pu : m_pItems)
	{
		pu->Draw();
	}
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* pu : m_pItems)
	{
		pu->Update(elapsedSec);
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	int hitIndex = -1;
	for (int i = 0; i < Size(); i++)
	{
		if (m_pItems[i]->IsOverlapping(rect))
		{
			hitIndex = i;
		}
	}

	if (hitIndex != -1)
	{
		PowerUp* p_Temp = m_pItems[hitIndex];
		m_pItems[hitIndex] = m_pItems[Size() - 1];
		m_pItems[Size() - 1] = p_Temp;

		delete m_pItems[Size() - 1];
		m_pItems[Size() - 1] = nullptr;
		m_pItems.pop_back();
		
		return true;
	}

	return false;

}
