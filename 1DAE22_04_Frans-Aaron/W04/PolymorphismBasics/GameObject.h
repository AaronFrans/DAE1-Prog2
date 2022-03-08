#pragma once
#include <string>

class GameObject
{
public:
	GameObject(int id );
	~GameObject( );
	// Implicitly defined copy/move constructors and operator= are ok
	std::string virtual ToString() const = 0;
protected:
	int m_Id;

private: 
};



