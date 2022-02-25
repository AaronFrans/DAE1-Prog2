#include "pch.h"
#include <iostream>
#include <iomanip>
#include "Time.h"

int Time::m_NrInstances = 0;

Time::Time( int seconds ):m_Seconds{seconds}
{
	std::cout << m_NrInstances;
	m_NrInstances++;
}
Time::Time( int seconds, int minutes ) : m_Seconds{ seconds + 60 * minutes }
{
	std::cout << m_NrInstances;
	m_NrInstances++;
}
Time::Time( int seconds, int minutes, int hours ) : m_Seconds{ seconds + 60 * minutes  + 3600 * hours}
{
	std::cout << m_NrInstances;
	m_NrInstances++;
}

Time::~Time()
{
	m_NrInstances--;
}

void Time::Print( ) const
{
	int hours{ m_Seconds / 3600 };
	int minutes{ m_Seconds % 3600 / 60 };
	int seconds{ m_Seconds % 3600 % 60 };
	std::cout << std::setw( 2 ) << std::setfill('0') << hours << ":";
	std::cout << std::setw( 2 ) << minutes << ":";
	std::cout << std::setw( 2 ) << seconds << std::endl;
}
int Time::GetSeconds( ) const
{
	return m_Seconds % 3600 % 60;
}
int Time::GetMinutes( ) const
{
	return m_Seconds % 3600 / 60;
}
int Time::GetHours( ) const
{
	return m_Seconds / 3600;
}

void Time::AddSeconds( int seconds )
{
	m_Seconds += seconds;
}
void Time::AddMinutes( int minutes )
{
	m_Seconds += minutes * 60;
}
void Time::AddHours( int hours )
{
	m_Seconds += hours * 3600;
}

int Time::GetNrInstances()
{
	return m_NrInstances;
}
