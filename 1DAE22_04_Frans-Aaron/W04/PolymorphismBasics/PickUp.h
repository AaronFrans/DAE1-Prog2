#pragma once
#include "GameObject.h"
#include <string>


class PickUp : public GameObject
{
public:
	PickUp( );
	~PickUp( );

	std::string virtual ToString() const override;

private:
	static int m_InstanceCounter;
};
