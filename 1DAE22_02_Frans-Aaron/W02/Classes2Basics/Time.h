#pragma once

class Time
{
public:
	Time( int seconds );
	Time( int seconds, int minutes );
	Time( int seconds, int minutes, int hours );
	
	~Time();

	void Print( ) const;
	int GetSeconds( ) const;
	int GetMinutes( ) const;
	int GetHours( ) const;

	void AddSeconds( int seconds );
	void AddMinutes( int minutes );
	void AddHours( int hours );

	static int GetNrInstances();


private:
	int m_Seconds{};
	static int m_NrInstances;
};