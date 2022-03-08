#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"

Game::Game()
{

}
Game::~Game()
{
	/*for (Enemy* ptr : m_pEnemies)
	{
		delete ptr;
	}
	m_pEnemies.clear();

	for (PickUp* ptr : m_pPickUps)
	{
		delete ptr;
	}
	m_pPickUps.clear();

	for (Weapon* ptr : m_pWeapons)
	{
		delete ptr;
	}
	m_pWeapons.clear();*/
	for (GameObject* ptr : m_pGameObjects)
	{
		delete ptr;
	}
	m_pGameObjects.clear();

}

void Game::AddEnemy()
{
	m_pGameObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	m_pGameObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	m_pGameObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };


	//for (Enemy* ptr : m_pEnemies)
	//{
	//	++seqNr;
	//	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	//}
	//for (PickUp* ptr : m_pPickUps)
	//{
	//	++seqNr;
	//	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	//}
	//for (Weapon* ptr : m_pWeapons)
	//{
	//	++seqNr;
	//	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	//}

	std::cout << "--> All Game objects\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}
}

void Game::ReportEnemies() const
{
	std::cout << "--> Enemies\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		Enemy* pEnemy{ dynamic_cast<Enemy*>(ptr) };
		if (pEnemy)
			std::cout << ptr->ToString() << "\n";
	}
}