#include "pch.h"
#include "TearManager.h"
#include "Texture.h"

TearManager::TearManager(Texture* texture)
	: m_NrShotTears{ 0 }
{
	for (int i = 0; i < m_NrTears; i++)
	{
		m_pTears.push_back(new Tear{ texture });
	}
}

TearManager::~TearManager()
{

	for (int i = 0; i < m_NrTears; i++)
	{
		delete m_pTears[i];

		m_pTears[i] = nullptr;
	}
}

void TearManager::DrawTears() const
{
	for (Tear* tear : m_pTears)
	{
		if (tear->GetState() == Tear::TearState::active)
			tear->Draw();
	}
}

void TearManager::UpdateTears(float elapsedSec)
{
	for (Tear* tear : m_pTears)
	{
		if (tear->GetState() == Tear::TearState::active)
			tear->Update(elapsedSec);
	}
}

Tear* TearManager::ShootTear()
{
	int i{ -1 };
	bool foundFreeBullet{ false };
	do {
		i++;
		if (m_pTears[i]->GetState() == Tear::TearState::inactive)
			foundFreeBullet = true;
	} while (foundFreeBullet != true);

	m_pTears[i]->SetState(Tear::TearState::active);
	return m_pTears[i];
}
