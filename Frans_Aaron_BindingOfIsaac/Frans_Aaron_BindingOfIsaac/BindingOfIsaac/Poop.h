#pragma once
#include "GameObject.h"
class Texture;

class Poop final : public GameObject
{

public:

	Poop(Texture* objectTexture, Point2f center, float size);

	Poop(const Poop& rhs);
	Poop(Poop && rhs) = default;
	Poop& operator=(const Poop & rhs);
	Poop& operator=(Poop && rhs) = default;
	~Poop();


	virtual void Draw() const override;

	void IsHit();

	virtual bool IsNotDestroyed() const override;

	virtual GameObject* Clone() const override;
private:

	int m_NrHitsTaken;
	int m_NrStates;
};

