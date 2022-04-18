#pragma once
#include "GameObject.h"

class Rock final : public GameObject
{
public:

    Rock(Texture* objectTexture, Point2f center, float size);

    virtual void Draw() const override;
    virtual bool IsNotDestroyed() const override;

private:
    bool m_IsBroken;
    int m_RockType;
};

