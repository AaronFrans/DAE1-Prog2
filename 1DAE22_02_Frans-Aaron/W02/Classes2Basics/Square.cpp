#include "pch.h"
#include "Square.h"
#include <iostream>
#include <iomanip>

Square::Square(float size)
	: Square(size, 0, 0)
{
	std::cout << "Constructor: Square( float size ), creates resources" << std::endl;
}
Square::Square(float size, float left, float bottom)
	: m_Size{ size }
	, m_Left{ left }
	, m_Bottom{ bottom }
{
	std::cout << "Constructor: Square( float left, float bottom, float size ), creates resources" << std::endl;
}

Square::~Square()
{
	std::cout << "Square destructor: release the resources\n";
}


void Square::Print()
{
	std::cout << std::fixed;
	std::cout << "Left: ";
	std::cout << std::setprecision(2) << m_Left;

	std::cout << ", bottom: ";
	std::cout << std::setprecision(2) << m_Bottom << std::endl;

	std::cout << "Size: ";
	std::cout << std::setprecision(2) << m_Size << std::endl;

	std::cout << "Perimeter: ";
	std::cout << std::setprecision(2) << GetPerimeter() << std::endl;;
	std::cout << "Area: ";
	std::cout << std::setprecision(2) << GetArea() << std::endl;;
}

void Square::Translate(float deltaLeft, float deltaBottom)
{
	m_Left += deltaLeft;
	m_Bottom += deltaBottom;
}
void Square::SetSize(float newSize)
{
	m_Size = newSize;
}

float Square::GetArea()
{
	return m_Size * m_Size;
}

float Square::GetPerimeter()
{
	return 4 * m_Size;
}
