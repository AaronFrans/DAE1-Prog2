#include "pch.h"
#include "Container.h"

Container::Container(int capacity)
	: m_Capacity{ capacity }
	, m_Size{ 0 }
{
	m_pElement = new int[capacity];
}

Container::~Container()
{
	delete[] m_pElement;
	m_pElement = nullptr;
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	return m_pElement[index];
}

void Container::Set(int index, int newValue)
{
	m_pElement[index] = newValue;
}

void Container::PushBack(int element)
{
	m_pElement[m_Size] = element;
	m_Size++;
	if (m_Capacity == m_Size )
	{
		Reserve(m_Capacity * 2 + 1);
	}
}

void Container::Reserve(int newCapacity)
{
	int* temp = new int[newCapacity];
	if (newCapacity > m_Capacity)
	{
		for (int i = 0; i < m_Capacity; i++)
		{
			temp[i] = m_pElement[i];
		}
		delete[] m_pElement;
		m_pElement = temp;
		m_Capacity = newCapacity;
	}

}
