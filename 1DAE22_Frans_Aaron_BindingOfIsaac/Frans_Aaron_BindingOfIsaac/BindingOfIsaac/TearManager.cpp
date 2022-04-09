#include "pch.h"
#include "TearManager.h"
#include "Texture.h"
#include "GameObject.h"

TearManager::TearManager()
{
	for (int i = 0; i < m_NrTears; i++)
	{
		m_pTears.push_back(new Tear{});
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

void TearManager::DrawFrontTears() const
{
	for (Tear* tear : m_pTears)
	{
		if (tear->GetState() != Tear::TearState::inactive && tear->GetIsFront())
			tear->Draw();
	}
}

void TearManager::DrawBackTears() const
{
	for (Tear* tear : m_pTears)
	{
		if (tear->GetState() != Tear::TearState::inactive && !tear->GetIsFront())
			tear->Draw();
	}
}



void TearManager::UpdateTears(float elapsedSec, std::vector<GameObject*> gameObjects)
{
	for (Tear* tear : m_pTears)
	{
		if (tear->GetState() != Tear::TearState::inactive)
		{
			tear->Update(elapsedSec, gameObjects);

		}
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
