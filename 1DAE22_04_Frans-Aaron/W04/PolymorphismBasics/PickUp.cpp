#include "pch.h"
#include "PickUp.h"
#include <iostream>


int PickUp::m_InstanceCounter = 0;

PickUp::PickUp()
	:GameObject(m_InstanceCounter + 1)
{
	std::cout << ">PickUp constructor<\n";
	++m_InstanceCounter;
}

PickUp::~PickUp()
{
	std::cout << ">PickUp destructor<\n";
}

std::string PickUp::ToString( ) const
{
	return std::string("PickUp ") + std::to_string(m_Id);
}


