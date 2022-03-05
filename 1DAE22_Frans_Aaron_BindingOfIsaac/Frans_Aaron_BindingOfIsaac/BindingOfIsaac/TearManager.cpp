#include "pch.h"
#include "TearManager.h"

TearManager::TearManager()
	: m_NrShotTears{ 0 }
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

void TearManager::ShootTear(const Point2f& tearPos, const float& tearRadius, const Vector2f& tearVelocity, const float& tearHeight)
{
	m_pTears[m_NrShotTears]->SetState(Tear::TearState::active);
	m_pTears[m_NrShotTears]->SetHeight(tearHeight);
	m_pTears[m_NrShotTears]->SetTearShape(Circlef{ tearPos, tearRadius });
	m_pTears[m_NrShotTears]->SetVelocity(tearVelocity);
}
