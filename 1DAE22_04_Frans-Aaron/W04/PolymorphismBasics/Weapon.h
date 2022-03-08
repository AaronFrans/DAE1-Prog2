#pragma once
#include "GameObject.h"
#include <string>


class Weapon : public GameObject
{
public:
	Weapon( );
	~Weapon( ); 

	std::string virtual ToString() const override;

private:
	static int m_InstanceCounter;
};

 
