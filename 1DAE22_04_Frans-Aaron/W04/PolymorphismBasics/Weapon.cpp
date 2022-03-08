#include "pch.h"
#include "Weapon.h"
#include <iostream>

int Weapon::m_InstanceCounter = 0;

Weapon::Weapon()
	:GameObject(m_InstanceCounter + 1)
{
	std::cout << ">Weapon constructor<\n";
	++m_InstanceCounter;
}

Weapon::~Weapon()
{
	std::cout << ">Weapon destructor<\n";
}


std::string Weapon::ToString( ) const
{
	return std::string("Weapon ") + std::to_string(m_Id);
}