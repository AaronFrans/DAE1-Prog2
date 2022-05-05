#pragma once
#include "GameObject.h"
class Texture;

class Poop final : public GameObject
{

public:

	Poop(Texture* objectTexture, Point2f center, float size);


	virtual void Draw() const override;

	void IsHit();

	virtual bool IsNotDestroyed() const override;

private:

	int m_NrHitsTaken;
	int m_NrStates;
};

