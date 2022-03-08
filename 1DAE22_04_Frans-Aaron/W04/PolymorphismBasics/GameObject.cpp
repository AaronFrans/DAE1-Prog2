#include "pch.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(int id)
	:m_Id{ id }
{
	std::cout << ">GameObject constructor<\n";
}

GameObject::~GameObject( )
{
	std::cout << ">GameObject destructor<\n";
}

