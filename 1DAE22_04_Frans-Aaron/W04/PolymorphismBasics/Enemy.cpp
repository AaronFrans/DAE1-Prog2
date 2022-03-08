#include "pch.h"
#include "Enemy.h"
#include <iostream>


int Enemy::m_InstanceCounter = 0;

Enemy::Enemy( )
	:GameObject(m_InstanceCounter + 1)
{
	std::cout << ">Enemy constructor<\n";
	++m_InstanceCounter;
}

Enemy::~Enemy()
{
	std::cout << ">Enemy destructor<\n";
}

std::string Enemy::ToString( ) const
{
	return std::string("Enemy ")  + std::to_string(m_Id);
}
